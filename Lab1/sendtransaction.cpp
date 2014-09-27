#include "sendtransaction.h"

#include <QDataStream>
#include <QFile>
#include <QUdpSocket>

#include "helpers.h"
#include "message.h"

SendTransaction::SendTransaction(int timeout, int MTU, int max_retransmissions, QObject *parent)
    : QObject(parent),
      timeout_(timeout),
      max_retransmissions_(max_retransmissions)
{
    data_size_ = MTU -
            sizeof(Message::data) -
            sizeof(Message::id) -
            sizeof(Message::seq);
}

void SendTransaction::Go(const QHostAddress& addr, quint16 port, QFile* file)
{
    addr_ = addr;
    port_ = port;
    file->setParent(this);
    file_ = file;
    socket_.bind();
    seq_ = 0;
    id_ = 0;

    RequestId();
}

void SendTransaction::SendMessage(quint32 state, const QByteArray& data)
{
    QByteArray datagram;
    QDataStream stream(&datagram, QIODevice::ReadWrite);
    stream << Message(state, seq_, id_, data);
    socket_.writeDatagram(datagram, addr_, port_);
    ++seq_;
}

bool SendTransaction::TransmitMessage(quint32 state, const QByteArray& data)
{
    for (int tr = 0; tr < max_retransmissions_; ++tr)
    {
        SendMessage(state, data);
        if (socket_.waitForReadyRead(timeout_))
        {
            return true;
        }
    }
    return false;
}

bool SendTransaction::ReceiveMessage(Message& message)
{
    while (socket_.hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(socket_.pendingDatagramSize());
        socket_.readDatagram(datagram.data(), datagram.size());
        Message msg(datagram);
        if (msg.seq == seq_ - 1)
        {
            message = msg;
            return true;
        }
    }
    return false;
}

void SendTransaction::RequestId()
{
    connect(&socket_, SIGNAL(readyRead()), this, SLOT(IdReceived()));
    if (!TransmitMessage(State::Request::REQ_ID, file_->fileName().toUtf8()))
    {
        socket_.disconnect();
        emit TransmissionFailed(State::Error::RETRANSMISSION_FAILED);
    }
}

void SendTransaction::IdReceived()
{
    socket_.disconnect();

    Message msg;
    if (!ReceiveMessage(msg))
    {
        RequestId();
        return;
    }

    if (!file_->isOpen())
    {
        file_->open(QIODevice::ReadOnly);
    }

    emit StartSending();
    bytes_total_ = file_->size();
    bytes_sent_ = 0;
    current_block_ = file_->read(data_size_);
    SendData();
}

void SendTransaction::SendData()
{
    if (current_block_.size() == 0)
    {
        SendFinished();
        return;
    }

    connect(&socket_, SIGNAL(readyRead()), this, SLOT(DataReceived()));

    if (!TransmitMessage(State::Request::SEND_DATA, current_block_))
    {
        socket_.disconnect();
        emit TransmissionFailed(State::Error::RETRANSMISSION_FAILED);
    }
}

void SendTransaction::DataReceived()
{
    socket_.disconnect();

    Message msg;
    if (ReceiveMessage(msg) && msg.state == State::Response::RECV_DATA)
    {
        bytes_sent_ += current_block_.size();
        emit Progress(bytes_sent_, bytes_total_);
        current_block_ = file_->read(data_size_);
    }
    SendData();
}

void SendTransaction::SendFinished()
{
    connect(&socket_, SIGNAL(readyRead()), this, SLOT(FinishReceived()));

    if (!TransmitMessage(State::Request::SEND_FINISH))
    {
        emit TransmissionFailed(State::Error::RETRANSMISSION_FAILED);
    }
}

void SendTransaction::FinishReceived()
{
    socket_.disconnect();

    Message msg;
    if (!ReceiveMessage(msg) || msg.state != State::Response::RECV_FINISH)
    {
        emit TransmissionFailed(State::Error::RETRANSMISSION_FAILED);
    }

    emit FinishSending();
}
