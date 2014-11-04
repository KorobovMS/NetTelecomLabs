#include "icmpheaderformatter.h"

#include <QTextStream>

ICMPHeaderFormatter::ICMPHeaderFormatter(const ICMPSegment& icmp)
{
    QTextStream stream(str_, QIODevice::WriteOnly);
    stream << "Type=" << type << "\n"
           << "Code=" << code << "\n"
           << "CRC=" << crc << "\n";
    stream.flush();
}

const QString&ICMPHeaderFormatter::GetString() const
{
    return str_;
}
