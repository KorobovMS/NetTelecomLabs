#include "sendtransaction.h"

#include <QDataStream>
#include <QFile>
#include <QUdpSocket>

#include "helpers.h"
#include "message.h"

SendTransaction::SendTransaction(int timeout,
                                 int MTU,
                                 int max_retransmissions,
                                 QObject *parent)
    : QObject(parent),
      timeout_(timeout),
      max_retransmissions_(max_retransmissions)
{
    // For explanation see "Serializing Qt Data Types" in docs
    typedef quint32 ByteArrayLengthType;

    data_size_ = MTU -
            sizeof(Message::state) -
            sizeof(ByteArrayLengthType) -
            sizeof(Message::id) -
            sizeof(Message::seq);
}

void SendTransaction::Go(const QHostAddress& addr, quint16 port, FilePtr file)
{
    addr_ = addr;
    port_ = port;
    file_ = file;
    bytes_total_ = file_->size();
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
        if (msg.seq == seq_)
        {
            message = msg;
            ++seq_;
            return true;
        }
    }
    return false;
}

void SendTransaction::MakeFileData(QByteArray& file_data)
{
    QDataStream stream(&file_data, QIODevice::WriteOnly);
    stream << file_->fileName() << bytes_total_;
}

void SendTransaction::RequestId()
{
    connect(&socket_, SIGNAL(readyRead()), this, SLOT(IdReceived()));

    QByteArray fileData;
    MakeFileData(fileData);
    if (!TransmitMessage(State::Request::REQ_ID, fileData))
    {
        disconnect(&socket_, SIGNAL(readyRead()), 0, 0);
        emit TransmissionFailed(State::Error::RETRANSMISSION_FAILED);
    }
}

void SendTransaction::IdReceived()
{
    disconnect(&socket_, SIGNAL(readyRead()), 0, 0);

    Message msg;
    if (!ReceiveMessage(msg) || msg.state != State::Response::RESP_ID)
    {
        emit TransmissionFailed(State::Error::ID_RECEIVING_FAILED);
        return;
    }
    id_ = msg.id;

    if (!file_->isOpen())
    {
        file_->open(QIODevice::ReadOnly);
    }
    else if (!file_->isReadable())
    {
        file_->close();
        file_->open(QIODevice::ReadOnly);
    }
    bytes_sent_ = 0;
    current_block_ = file_->read(data_size_);

    emit StartSending();
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
        disconnect(&socket_, SIGNAL(readyRead()), 0, 0);
        emit TransmissionFailed(State::Error::RETRANSMISSION_FAILED);
    }
}

void SendTransaction::DataReceived()
{
    disconnect(&socket_, SIGNAL(readyRead()), 0, 0);

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
    disconnect(&socket_, SIGNAL(readyRead()), 0, 0);

    Message msg;
    if (!ReceiveMessage(msg) || msg.state != State::Response::RECV_FINISH)
    {
        emit TransmissionFailed(State::Error::FINISH_FAILED);
    }

    socket_.close();
    emit FinishSending();
}
