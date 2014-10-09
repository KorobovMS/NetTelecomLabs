#include "sendtransaction.h"

#include <QDataStream>
#include <QFile>
#include <QFileInfo>
#include <QUdpSocket>

#include "helpers.h"
#include "message.h"

SendTransaction::SendTransaction(const QHostAddress& addr,
                                 quint16 port,
                                 FilePtr file,
                                 int timeout,
                                 int MTU,
                                 int max_retransmissions,
                                 QObject *parent)
    : QObject(parent)
{
    // For explanation see "Serializing Qt Data Types" in docs
    typedef quint32 ByteArrayLengthType;

    data_size_ = MTU -
            sizeof(Message::state) -
            sizeof(ByteArrayLengthType) -
            sizeof(Message::id) -
            sizeof(Message::seq);
    timeout_ = timeout;
    max_retransmissions_ = max_retransmissions;
    addr_ = addr;
    port_ = port;
    file_ = file;
    bytes_total_ = file_->size();
    socket_.bind();
    seq_ = 0;
    id_ = 0;
}

void SendTransaction::Go()
{
    if (!RequestId())
    {
        emit TransmissionFailed(State::Error::ID_RECEIVING_FAILED);
        return;
    }

    PrepareFile();

    if (!SendFile())
    {
        emit TransmissionFailed(State::Error::SEND_DATA_FAILED);
        return;
    }

    if (!FinishSending())
    {
        emit TransmissionFailed(State::Error::FINISH_FAILED);
        return;
    }
}

bool SendTransaction::RequestId()
{
    QByteArray fileData;
    MakeFileData(fileData);
    if (!TransmitMessage(State::Request::REQ_ID, fileData))
    {
        return false;
    }

    Message msg;
    if (!ReceiveMessage(msg) || msg.state != State::Response::RESP_ID)
    {
        return false;
    }

    id_ = msg.id;
    return true;
}

void SendTransaction::PrepareFile()
{
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
    emit TransmissionStarted();
}

bool SendTransaction::SendFile()
{
    QByteArray current_block = file_->read(data_size_);
    while (current_block.size() != 0)
    {
        if (!TransmitMessage(State::Request::SEND_DATA, current_block))
        {
            return false;
        }

        Message msg;
        if (!ReceiveMessage(msg) || msg.state != State::Response::RECV_DATA)
        {
            return false;
        }

        bytes_sent_ += current_block.size();
        emit TransmissionProgress(bytes_sent_, bytes_total_);
        current_block = file_->read(data_size_);
    }

    return true;
}

bool SendTransaction::FinishSending()
{
    if (!TransmitMessage(State::Request::SEND_FINISH))
    {
        return false;
    }

    Message msg;
    if (!ReceiveMessage(msg) || msg.state != State::Response::RECV_FINISH)
    {
        return false;
    }

    emit TransmissionFinished();

    socket_.close();
    return true;
}

bool SendTransaction::SendMessage(quint32 state, const QByteArray& data)
{
    QByteArray datagram;
    QDataStream stream(&datagram, QIODevice::ReadWrite);
    stream << Message(state, seq_, id_, data);
    qint64 sent = socket_.writeDatagram(datagram, addr_, port_);
    return sent == datagram.size();
}

bool SendTransaction::TransmitMessage(quint32 state, const QByteArray& data)
{
    for (int tr = 0; tr < max_retransmissions_; ++tr)
    {
        bool success = SendMessage(state, data);
        if (success && socket_.waitForReadyRead(timeout_))
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
    QFileInfo info(file_->fileName());
    stream << info.fileName() << bytes_total_;
}
