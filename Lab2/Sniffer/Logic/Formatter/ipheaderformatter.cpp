#include "ipheaderformatter.h"

#include <QHostAddress>
#include <QTextStream>

IPHeaderFormatter::IPHeaderFormatter(const IPPacket& ip)
{
    QTextStream stream(&str_, QIODevice::WriteOnly);
    stream << "Version: " << (ip.ver_ihl >> 4) << "\n"
           << "IHL: " << (ip.ver_ihl & 0x0F) << "\n"
           << "TOS: " << ip.tos << "\n"
           << "Packet length: " << ip.tlen << "\n"
           << "ID: " << ip.id << "\n"
           << "Flags: " <<
              ((ip.flags_fo >> 15) & 1) << " " <<
              (((ip.flags_fo >> 14) & 1) ? "DF " : " ") <<
              (((ip.flags_fo >> 13) & 1) ? "MF" : "" ) << "\n"
           << "Fragment offset: " << (ip.flags_fo & 0x1FFF) << "\n"
           << "TTL: " << ip.ttl << "\n"
           << "Protocol: " << ip.proto << "\n"
           << "CRC: " << ip.crc << "\n"
           << "Source: " << QHostAddress(ip.src_addr).toString() << "\n"
           << "Destination: " << QHostAddress(ip.dst_addr).toString() << "\n";
    stream.flush();
}

const QString& IPHeaderFormatter::GetString() const
{
    return str_;
}
