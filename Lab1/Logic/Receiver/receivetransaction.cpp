#include "receivetransaction.h"

#include <QDataStream>
#include <QFile>
#include <QUdpSocket>
#include <QDir>
#include <QThread>

#include "helpers.h"
#include "message.h"

ReceiveTransaction::ReceiveTransaction(RequestInfo ri, QString dir) :
    req_info_(ri),
    is_active_(true),
    dir_(dir)
{
}

void ReceiveTransaction::Go()
{
    socket_ = new QUdpSocket;
    connect(this->thread(), SIGNAL(finished()),
            socket_, SLOT(deleteLater()));
    socket_->bind(req_info_.host_ip_);

    QString filepath = QDir::cleanPath(
                dir_ + QDir::separator() + req_info_.filename_);
    file_ = new QFile(filepath);
    connect(this->thread(), SIGNAL(finished()),
            file_, SLOT(deleteLater()));
    file_->open(QIODevice::WriteOnly);

    SendId();
    last_seq_ = 0;
    bytes_received_ = 0;

    emit StartReceiving();

    const int for_all_eternity = -1;    
    while (is_active_)
    {
        socket_->waitForReadyRead(for_all_eternity);
        ReceiveMessage();
    }
}

void ReceiveTransaction::SendId()
{
    QByteArray data;
    QDataStream ds(&data, QIODevice::ReadWrite);
    QByteArray peer_info;
    QDataStream peer_info_stream(&peer_info, QIODevice::ReadWrite);
    peer_info_stream << socket_->localAddress() << socket_->localPort();
    ds << Message(State::Response::RESP_ID, 0, req_info_.id_, peer_info);
    socket_->writeDatagram(data, req_info_.client_ip_, req_info_.client_port_);
}

void ReceiveTransaction::ReceiveMessage()
{
    while (socket_->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(socket_->pendingDatagramSize());
        socket_->readDatagram(datagram.data(), datagram.size());
        Message msg(datagram);

        if (msg.state == State::Request::SEND_DATA)
        {
            if (last_seq_ < msg.seq)
            {
                last_seq_ = msg.seq;
                file_->write(msg.data.data(), msg.data.size());
                bytes_received_ += msg.data.size();
                emit Progress(bytes_received_, req_info_.filesize_);
            }
            SendMessage(State::Response::RECV_DATA, msg.id, msg.seq);
        }
        else if (msg.state == State::Request::SEND_FINISH)
        {
            SendFinish(msg);
        }
    }
}

void ReceiveTransaction::SendMessage(quint32 state, quint32 id, quint32 seq)
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::ReadWrite);
    stream << Message(state, seq, id, QByteArray());
    socket_->writeDatagram(data, req_info_.client_ip_, req_info_.client_port_);
}

void ReceiveTransaction::SendFinish(Message& msg)
{
    is_active_ = false;
    emit FinishReceiving();
    QByteArray data;
    QDataStream ds(&data, QIODevice::ReadWrite);
    ds << Message(State::Response::RECV_FINISH, msg.seq, msg.id, QByteArray());
    socket_->writeDatagram(data, req_info_.client_ip_, req_info_.client_port_);
}
