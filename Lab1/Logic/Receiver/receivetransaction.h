#ifndef RECEIVETRANSACTION_H
#define RECEIVETRANSACTION_H

#include <QObject>
#include <QUdpSocket>
#include <QVector>

#include "requestinfo.h"

struct Message;
class QByteArray;
class QUdpSocket;
class QHostAddress;
class QFile;

class ReceiveTransaction : public QObject
{
    Q_OBJECT

public:
    ReceiveTransaction(RequestInfo ri, QString dir);

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

    RequestInfo req_info_;
    QString dir_;
    QUdpSocket* socket_;
    QFile* file_;
    quint32 last_seq_;
    quint64 bytes_received_;
    bool is_active_;
};

#endif // RECEIVETRANSACTION_H
