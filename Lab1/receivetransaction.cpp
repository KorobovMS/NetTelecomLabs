#include "receivetransaction.h"

#include <QDataStream>
#include <QFile>
#include <QUdpSocket>
#include <QDir>

#include "helpers.h"
#include "message.h"

ReceiveTransaction::ReceiveTransaction( QHostAddress addr, quint16 port )
{

    addr_ = addr;
    port_ = port;

    socket_.bind();
    //PendingMessage();
    connect( &socket_ ,SIGNAL( readyRead() ), this, SLOT( PendingMessage() ) );
}

void ReceiveTransaction::PendingMessage()
{
    while( 1 )
    {
        socket_.waitForReadyRead( -1 );//Всегда в ожидании.
        ReceiveMessage();
    }
}

bool ReceiveTransaction::ReceiveMessage( )
{
    while( socket_.hasPendingDatagrams() ) //Ожидаем сообщения
    {
        QByteArray datagram;
        datagram.resize( socket_.pendingDatagramSize() );
        socket_.readDatagram( datagram.data(), datagram.size() );
        Message msg( datagram );

        if( msg.state == State::Request::REQ_ID )
        {
            RegId( msg );
            return true;
        }
        else if( msg.state == State::Request::SEND_DATA )
        {
            if ( last_seq_for_id_[ msg.id ] < msg.seq )
            {
                last_seq_for_id_[ msg.id ] = msg.id;
                LoadFile( msg );
            }
            SendMessage( State::Response::RECV_DATA, msg.id, msg.seq  );
            return true;
        }
        else if( msg.state == State::Request::SEND_FINISH )
        {
            SendFinish( msg );
        }

    }
    return false;
}

void ReceiveTransaction::SendMessage( quint32 state, quint32 id,  quint32 seq )
{
    QByteArray datagram;
    QDataStream stream( &datagram, QIODevice::ReadWrite );
    stream << Message( state, seq, id, 0 );
    socket_.writeDatagram( datagram, addr_, port_ );
}

void ReceiveTransaction::RegId( Message& msg )
{
    QDataStream in( msg.data );
    QString fName;
    quint64 bytesTotal;
    in >> fName >> bytesTotal;
    //Progress( bytes_received, bytes_total )

    while( 1 )
    {
        quint32 ID = rand() % UINT_MAX;
        QMap< quint32, QString >::iterator p = file_for_id_.find( ID );
        if( p != file_for_id_.end( ) )
        {
            file_for_id_.insert( ID, fName );
            SendMessage( State::Response::RESP_ID, ID, msg.seq );
            break;
        }
    }
}

void ReceiveTransaction::DelId( Message& msg )
{
    QMap < quint32, QString >::iterator p = file_for_id_.find( msg.id );
    file_for_id_.erase( p );
    QMap < quint32, quint32 >::iterator p1 = last_seq_for_id_.find( msg.id );
    last_seq_for_id_.erase( p1 );
}

void ReceiveTransaction::LoadFile( Message &msg  )
{
    QFile file;
    QDir::setCurrent("/tmp");
    file.setFileName( file_for_id_[ msg.id ] );
    QDir::setCurrent( '/' + DOWNLOADS );
    file.open( QIODevice :: Append | QIODevice :: WriteOnly  );
    QDataStream  out( &file );
    out << msg.data;
    file.close();
}


void ReceiveTransaction::SendFinish( Message& msg )
{
    QByteArray datagram;
    QDataStream stream( &datagram, QIODevice::ReadWrite );
    stream << Message( State::Response::RECV_FINISH, msg.seq, msg.id, 0 );
    socket_.writeDatagram( datagram, addr_, port_ );
}








