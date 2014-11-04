#include "udpheaderformatter.h"

#include <QTextStream>

UDPHeaderFormatter::UDPHeaderFormatter(const UDPSegment& udp)
{
    QTextStream stream(str_, QIODevice::WriteOnly);
    stream << "Source port: " << udp.src_port << "\n"
           << "Destination port: " << udp.dst_port << "\n"
           << "Length: " << udp.length << "\n"
           << "CRC: " << QString("0x%1").arg(udp.crc, 0, 16) << "\n";
    stream.flush();
}

const QString& UDPHeaderFormatter::GetString() const
{
    return str_;
}
