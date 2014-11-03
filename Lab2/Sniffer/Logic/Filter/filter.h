#ifndef FILTER_H
#define FILTER_H

#include <QHostAddress>
#include <QObject>
#include <QSet>
#include <QString>

#include "ippacket.h"

class Filter : public QObject
{
    Q_OBJECT

public:
    explicit Filter(QObject* parent = 0);

    bool Apply(const IPPacket& packet) const;
    bool IsRawApplied() const;

    void AddProtocol(quint8 protocol);
    void AddFrom(const QHostAddress& from);
    void AddTo(const QHostAddress& to);
    void AddRawFormat();

private:
    typedef QSet<quint8> Protocols;
    typedef QSet<QHostAddress> Addresses;

    Protocols protocols_;
    Addresses from_;
    Addresses to_;
    bool is_raw_applied_;
};

#endif // FILTER_H
