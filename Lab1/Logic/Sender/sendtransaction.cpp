#include "sendtransaction.h"

#include <QDataStream>
#include <QFile>
#include <QFileInfo>
#include <QThread>
#include <QUdpSocket>

#include "helpers.h"
#include "message.h"
#include "settings.h"

SendTransaction::SendTransaction(const QHostAddress& addr,
                                 quint16 port,
                                 FilePtr file,
                                 QObject* parent)
    : QObject(parent)
{
    Settings s;
    int MTU;
    s.GetUdpMTU(MTU);
    s.GetMaxRetransmissions(max_retransmissions_);
    s.GetTimeoutForSending(timeout_for_sending_);
    s.GetTimeoutForPermission(timeout_for_permission_);

    // For explanation see "Serializing Qt Data Types" in docs
    typedef quint32 ByteArrayLengthType;

    data_size_ = MTU -
            sizeof(Message::state) -
            sizeof(ByteArrayLengthType) -
            sizeof(Message::id) -
            sizeof(Message::seq);
    addr_ = addr;
    port_ = port;
    file_ = file;
    bytes_total_ = file_->size();
    seq_ = 0;
    id_ = 0;
}

void SendTransaction::Go()
{
    socket_ = new QUdpSocket;
    connect(this->thread(), SIGNAL(finished()),
            socket_, SLOT(deleteLater()));
    socket_->bind();

    timeout_ = timeout_for_permission_;
    if (!RequestId())
    {
        return;
    }

    PrepareFile();

    timeout_ = timeout_for_sending_;
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

    emit TransmissionFinished();
}

bool SendTransaction::RequestId()
{
    QByteArray fileData;
    MakeFileData(fileData);
    if (!TransmitMessage(State::Request::REQUEST_PERMISSION, fileData))
    {
        emit TransmissionFailed(State::Error::ID_RECEIVING_FAILED);
        return false;
    }

    Message msg;
    if (!ReceiveMessage(msg))
    {
        emit TransmissionFailed(State::Error::ID_RECEIVING_FAILED);
        return false;
    }

    if (msg.state == State::Response::TRANSMISSION_DECLINED)
    {
        emit TransmissionCancelled();
        return false;
    }

    if (msg.state != State::Response::RESP_ID)
    {
        emit TransmissionFailed(State::Error::ID_RECEIVING_FAILED);
        return false;
    }

    MakePeerData(msg, addr_, port_);
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

    socket_->close();
    file_->close();
    return true;
}

bool SendTransaction::SendMessage(quint32 state, const QByteArray& data)
{
    QByteArray datagram;
    QDataStream stream(&datagram, QIODevice::ReadWrite);
    stream << Message(state, seq_, id_, data);
    qint64 sent = socket_->writeDatagram(datagram, addr_, port_);
    return sent == datagram.size();
}

bool SendTransaction::TransmitMessage(quint32 state, const QByteArray& data)
{
    for (int tr = 0; tr < max_retransmissions_; ++tr)
    {
        bool success = SendMessage(state, data);
        if (success && socket_->waitForReadyRead(timeout_))
        {
            return true;
        }
    }
    return false;
}

bool SendTransaction::ReceiveMessage(Message& message)
{
    while (socket_->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(socket_->pendingDatagramSize());
        socket_->readDatagram(datagram.data(), datagram.size());
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

void SendTransaction::MakePeerData(const Message& msg, QHostAddress& addr,
                                   quint16& port)
{
    QDataStream stream(msg.data);
    stream >> addr >> port;
}
