#include "receivetransaction.h"

#include <QDataStream>
#include <QFile>
#include <QUdpSocket>
#include <QDir>
#include <QThread>

#include "helpers.h"
#include "message.h"

ReceiveTransaction::ReceiveTransaction(QHostAddress host, QHostAddress addr, quint16 port,
                                       QString filename, quint64 filesize,
                                       quint32 id)
{
    host_addr_ = host;
    addr_ = addr;
    port_ = port;
    filename_ = filename;
    filesize_ = filesize;
    id_ = id;
    is_active_ = true;
    qDebug() << "RT" << addr << port << filename << filesize << id;
}

void ReceiveTransaction::Go()
{
    socket_ = new QUdpSocket;
    connect(this->thread(), SIGNAL(finished()),
            socket_, SLOT(deleteLater()));
    socket_->bind(host_addr_);

    file_ = new QFile(filename_);
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
        socket_->waitForReadyRead( for_all_eternity );
        ReceiveMessage();
    }
}

void ReceiveTransaction::SendId()
{
    QByteArray datagram;
    QDataStream stream( &datagram, QIODevice::ReadWrite );
    QByteArray peer_info;
    QDataStream peer_info_stream(&peer_info, QIODevice::ReadWrite);
    peer_info_stream << socket_->localAddress() << socket_->localPort();
    stream << Message( State::Response::RESP_ID, 0, id_, peer_info);
    socket_->writeDatagram( datagram, addr_, port_ );
}

void ReceiveTransaction::ReceiveMessage( )
{
    while( socket_->hasPendingDatagrams() )
    {
        QByteArray datagram;
        datagram.resize( socket_->pendingDatagramSize() );
        socket_->readDatagram( datagram.data(), datagram.size() );
        Message msg( datagram );

        if( msg.state == State::Request::SEND_DATA )
        {
            if ( last_seq_ < msg.seq )
            {
                last_seq_ = msg.seq;
                file_->write(msg.data.data(), msg.data.size());
                bytes_received_ += msg.data.size();
                emit Progress(bytes_received_, filesize_);
            }
            SendMessage( State::Response::RECV_DATA, msg.id, msg.seq );
        }
        else if( msg.state == State::Request::SEND_FINISH )
        {
            SendFinish( msg );
        }
    }
}

void ReceiveTransaction::SendMessage( quint32 state, quint32 id, quint32 seq )
{
    QByteArray datagram;
    QDataStream stream( &datagram, QIODevice::ReadWrite );
    stream << Message( state, seq, id, 0 );
    socket_->writeDatagram( datagram, addr_, port_ );
}

void ReceiveTransaction::SendFinish( Message& msg )
{
    is_active_ = false;
    emit FinishReceiving();
    QByteArray datagram;
    QDataStream stream( &datagram, QIODevice::ReadWrite );
    stream << Message( State::Response::RECV_FINISH, msg.seq, msg.id, QByteArray( ) );
    socket_->writeDatagram( datagram, addr_, port_ );
}