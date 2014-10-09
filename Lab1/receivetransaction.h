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
    explicit ReceiveTransaction( QHostAddress addr, quint16 port );

signals:
    void StartReceiving();
    void Progress(int bytes_received, int bytes_total);
    void FinishSending();

private slots:
    void PendingMessage();

private:

    void SendMessage( quint32 state, quint32 id,  quint32 seq );
    void LoadFile( Message& msg  );
    bool ReceiveMessage( );
    void RegIdStore( Message& msg );
    void DelId( Message& msg );
    void RegId( Message& msg );
    void SendFinish( Message& msg );


    QMap < quint32, QString >  file_for_id_;
    QMap < quint32, quint32 > last_seq_for_id_;
    //QString path_;
    QUdpSocket socket_;
    QHostAddress addr_;
    quint16 port_;
    QFile* file_;
    int data_size_;
};

#endif // RECEIVETRANSACTION_H
