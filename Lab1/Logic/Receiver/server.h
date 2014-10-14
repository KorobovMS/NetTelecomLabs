#ifndef SERVER_H
#define SERVER_H

#include <QHostAddress>
#include <QObject>
#include <QUdpSocket>

#include "message.h"

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject* parent = 0);
    void SetHostAddress(const QHostAddress& addr);
    void SetPort(quint16 port);
    ~Server();

signals:
    void SocketBound(QHostAddress, quint16);
    void SocketNotBound();
    void NewRequest(QHostAddress, QHostAddress, quint16, QString, quint64, quint32);

public slots:
    void ServeForever();

private:
    void ProcessDatagrams();
    void RetrieveRequestInfo(const Message& msg,
                             QString& filename,
                             quint64& filesize);

private:
    QUdpSocket* socket_;
    QHostAddress* addr_;
    quint16* port_;
    bool is_active_;
    quint32 next_id_;
};

#endif // SERVER_H
