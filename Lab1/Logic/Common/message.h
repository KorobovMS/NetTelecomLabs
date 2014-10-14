#ifndef MESSAGE_H
#define MESSAGE_H

#include <QByteArray>
#include <QDataStream>

struct Message
{
public:
    Message();
    Message(QByteArray& datagram);
    Message(quint32 state, quint32 seq, quint32 id, const QByteArray& data);

    quint32 state;
    quint32 seq;
    quint32 id;
    QByteArray data;
};

QDataStream& operator<<(QDataStream& ds, const Message& msg);

#endif // MESSAGE_H
