#include "udpheaderformatter.h"

#include <QTextStream>

UDPHeaderFormatter::UDPHeaderFormatter(const UDPSegment& udp)
{
    QTextStream stream(str_, QIODevice::WriteOnly);
    stream << "Source port=" << udp.src_port << "\n"
           << "Destination port=" << udp.dst_port << "\n"
           << "Length=" << udp.length << "\n"
           << "CRC=" << udp.crc << "\n";
    stream.flush();
}

const QString&UDPHeaderFormatter::GetString() const
{
    return str_;
}
