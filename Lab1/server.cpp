#include "server.h"

#include <QByteArray>
#include <QHostAddress>
#include <QThread>

#include "helpers.h"

Server::Server(QObject* parent) :
    QObject(parent),
    addr_(0),
    port_(0),
    next_id_(1)
{
}

void Server::SetHostAddress(const QHostAddress& addr)
{
    if (addr_ == 0)
    {
        addr_ = new QHostAddress;
    }
    *addr_ = addr;
}

void Server::SetPort(quint16 port)
{
    if (port_ == 0)
    {
        port_ = new quint16;
    }
    *port_ = port;
}

Server::~Server()
{
    if (addr_ != 0)
    {
        delete addr_;
    }

    if (port_ != 0)
    {
        delete port_;
    }
}

void Server::ServeForever()
{
    qDebug() << "Serve forever";
    is_active_ = true;
    socket_ = new QUdpSocket;
    socket_->moveToThread(this->thread());
    connect(this->thread(), SIGNAL(finished()),
            socket_, SLOT(deleteLater()));

    if (addr_ == 0)
    {
        SetHostAddress(QHostAddress::LocalHost);
    }

    if (port_ == 0)
    {
        SetPort(0);
    }

    if (socket_->bind(*addr_, *port_))
    {
        emit SocketBound(*addr_, *port_);
        qDebug() << "Server socket is bound";
    }
    else
    {
        emit SocketNotBound();
        qDebug() << "Server socket is not bound";
        return;
    }

    const int for_all_eternity = -1;
    while (is_active_)
    {
        socket_->waitForReadyRead(for_all_eternity);
        ProcessDatagrams();
    }
}

void Server::ProcessDatagrams()
{
    while (socket_->hasPendingDatagrams())
    {
        QHostAddress addr;
        quint16 port;
        QByteArray datagram;
        datagram.resize(socket_->pendingDatagramSize());
        socket_->readDatagram(datagram.data(), datagram.size(), &addr, &port);
        Message msg(datagram);

        if (msg.state == State::Request::REQUEST_PERMISSION)
        {
            QString filename;
            quint64 filesize;
            RetrieveRequestInfo(msg, filename, filesize);
            emit NewRequest(socket_->localAddress(), addr, port, filename, filesize, next_id_);
            qDebug() << "New request";
            ++next_id_;
        }
        else if (msg.state == State::Request::KILL_YOURSELF)
        {
            qDebug() << "Kill Server";
            is_active_ = false;
        }
    }
}

void Server::RetrieveRequestInfo(const Message& msg,
                                 QString& filename,
                                 quint64& filesize)
{
    QDataStream stream(msg.data);
    stream >> filename >> filesize;
}
