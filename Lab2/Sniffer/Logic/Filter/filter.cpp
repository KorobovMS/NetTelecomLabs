#include "filter.h"

Filter::Filter(QObject* parent) :
    QObject(parent),
    is_raw_applied_(false)
{
}

bool Filter::Apply(const IPPacket& packet) const
{
    if (!protocols_.empty() && !protocols_.contains(packet.proto))
    {
        return false;
    }

    if (!from_.empty() && !from_.contains(QHostAddress(packet.src_addr)))
    {
        return false;
    }

    if (!to_.empty() && !to_.contains(QHostAddress(packet.dst_addr)))
    {
        return false;
    }

    return true;
}

bool Filter::IsRawApplied() const
{
    return is_raw_applied_;
}

void Filter::AddProtocol(quint8 protocol)
{
    protocols_.insert(protocol);
}

void Filter::AddFrom(const QHostAddress& from)
{
    from_.insert(from);
}

void Filter::AddTo(const QHostAddress& to)
{
    to_.insert(to);
}

void Filter::AddRawFormat()
{
    is_raw_applied_ = true;
}
