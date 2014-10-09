#ifndef SENDTRANSACTION_H
#define SENDTRANSACTION_H

#include <QObject>
#include <QUdpSocket>
#include <QSharedPointer>

#include "helpers.h"

struct Message;
class QByteArray;
class QUdpSocket;
class QHostAddress;
class QFile;

class SendTransaction : public QObject
{
    Q_OBJECT

public:
    SendTransaction(const QHostAddress& addr,
                    quint16 port,
                    FilePtr file,
                    int timeout = 5000,
                    int MTU = 512,
                    int mex_retransmissions = 5,
                    QObject *parent = 0);
public slots:
    void Go();

signals:
    void TransmissionStarted();
    void TransmissionProgress(int sent, int total);
    void TransmissionFinished();
    void TransmissionFailed(quint32 error_code);

private:
    void ProcessTransaction();
    bool RequestId();
    void PrepareFile();
    bool SendFile();
    bool FinishSending();

    bool SendMessage(quint32 state, const QByteArray& data = QByteArray());
    bool TransmitMessage(quint32 state, const QByteArray& data = QByteArray());
    bool ReceiveMessage(Message& message);
    void MakeFileData(QByteArray& file_data);

private:
    QUdpSocket* socket_;
    QHostAddress addr_;
    quint16 port_;
    FilePtr file_;
    quint32 seq_;
    quint32 id_;
    int timeout_;
    int data_size_;
    int max_retransmissions_;
    quint64 bytes_sent_;
    quint64 bytes_total_;
};

#endif // SENDTRANSACTION_H
