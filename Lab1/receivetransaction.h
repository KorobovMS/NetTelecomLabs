#ifndef RECEIVETRANSACTION_H
#define RECEIVETRANSACTION_H

#include <QObject>
#include <QUdpSocket>
#include <QVector>

struct Message;
class QByteArray;
class QUdpSocket;
class QHostAddress;
class QFile;

class ReceiveTransaction : public QObject
{
    Q_OBJECT

public:
    ReceiveTransaction( QHostAddress addr, quint16 port,
                        QString filename, quint64 filesize,
                        quint32 id );

signals:
    void StartReceiving();
    void Progress( int bytes_received, int bytes_total );
    void FinishReceiving();

private slots:
    void Go( );

private:
    void SendId();
    void SendMessage( quint32 state, quint32 id, quint32 seq );
    void ReceiveMessage( );
    void SendFinish( Message& msg );

    QHostAddress addr_;
    quint16 port_;
    QString filename_;
    quint64 filesize_;
    quint32 id_;

    QUdpSocket* socket_;
    QFile* file_;
    quint32 last_seq_;
    quint64 bytes_received_;
    bool is_active_;
};

#endif // RECEIVETRANSACTION_H
