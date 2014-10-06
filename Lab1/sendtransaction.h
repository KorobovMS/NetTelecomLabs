#ifndef SENDTRANSACTION_H
#define SENDTRANSACTION_H

#include <QObject>
#include <QUdpSocket>
#include <QVector>
#include <QSharedPointer>

struct Message;
class QByteArray;
class QUdpSocket;
class QHostAddress;
class QFile;

typedef QSharedPointer<QFile> FilePtr;

class SendTransaction : public QObject
{
    Q_OBJECT

public:
    explicit SendTransaction(int timeout = 5000,
                             int MTU = 512,
                             int mex_retransmissions = 5,
                             QObject *parent = 0);
    void Go(const QHostAddress& addr, quint16 port, FilePtr file);

signals:
    void StartSending();
    void Progress(int sent, int total);
    void FinishSending();
    void TransmissionFailed(quint32 error_code);

private:
    void SendMessage(quint32 state, const QByteArray& data = QByteArray());
    bool TransmitMessage(quint32 state, const QByteArray& data = QByteArray());
    bool ReceiveMessage(Message& message);
    void MakeFileData(QByteArray& file_data);

private slots:
    void RequestId();
    void IdReceived();
    void SendData();
    void DataReceived();
    void SendFinished();
    void FinishReceived();

private:
    QUdpSocket socket_;
    QHostAddress addr_;
    quint16 port_;
    FilePtr file_;
    quint32 seq_;
    quint32 id_;
    int timeout_;
    int data_size_;
    int max_retransmissions_;
    QByteArray current_block_;
    quint64 bytes_sent_;
    quint64 bytes_total_;
};

#endif // SENDTRANSACTION_H
