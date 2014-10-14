#include "message.h"

Message::Message()
{}

Message::Message(QByteArray& datagram)
{
    QDataStream stream(datagram);
    stream >> state >> seq >> id >> data;
}

Message::Message(quint32 state, quint32 seq, quint32 id, const QByteArray& data)
    : state(state),
      seq(seq),
      id(id),
      data(data)
{}

QDataStream& operator<<(QDataStream& ds, const Message& msg)
{
    ds << msg.state << msg.seq << msg.id << msg.data;
    return ds;
}
