#include "filter.h"

Filter::Filter(QObject* parent) :
    QObject(parent),
    is_raw_applied_(false)
{
}

bool Filter::Apply(const IPPacket& packet) const
{
    if (!from_.isNull() && from_ != QHostAddress(packet.src_addr))
    {
        return false;
    }

    if (!to_.isNull() && to_ != QHostAddress(packet.dst_addr))
    {
        return false;
    }

    return true;
}

bool Filter::IsRawApplied() const
{
    return is_raw_applied_;
}

const QString& Filter::GetWriter() const
{
    return writer_;
}

void Filter::SetFrom(const QHostAddress& from)
{
    from_ = from;
}

void Filter::SetTo(const QHostAddress& to)
{
    to_ = to;
}

void Filter::SetRawFormat()
{
    is_raw_applied_ = true;
}

void Filter::SetWriter(const QString& writer)
{
    writer_ = writer;
}
