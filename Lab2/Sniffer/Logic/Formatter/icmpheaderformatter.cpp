#include "icmpheaderformatter.h"

#include <QTextStream>

ICMPHeaderFormatter::ICMPHeaderFormatter(const ICMPSegment& icmp)
{
    QTextStream stream(str_, QIODevice::WriteOnly);
    stream << "Type: " << icmp.type << "\n"
           << "Code: " << icmp.code << "\n"
           << "CRC: " << icmp.crc << "\n";
    stream.flush();
}

const QString& ICMPHeaderFormatter::GetString() const
{
    return str_;
}
