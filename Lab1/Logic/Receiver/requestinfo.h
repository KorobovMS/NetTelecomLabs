#ifndef REQUESTINFO_H
#define REQUESTINFO_H

#include <QHostInfo>
#include <QString>

struct RequestInfo
{
    RequestInfo()
    {}

    RequestInfo(const QHostAddress& host_ip,
                const QHostAddress& client_ip, quint16 client_port,
                const QString& filename, quint64 filesize, quint32 id) :
        host_ip_(host_ip),
        client_ip_(client_ip),
        client_port_(client_port),
        filename_(filename),
        filesize_(filesize),
        id_(id)
    {}

    QHostAddress host_ip_;
    QHostAddress client_ip_;
    quint16 client_port_;
    QString filename_;
    quint64 filesize_;
    quint32 id_;
};

#endif // REQUESTINFO_H
