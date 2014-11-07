#include "tcpheaderformatter.h"

#include <QTextStream>

TCPHeaderFormatter::TCPHeaderFormatter(const TCPSegment& tcp)
{
    QTextStream stream(&str_, QIODevice::WriteOnly);
    stream << "Source port: " << tcp.src_port << "\n"
           << "Destination port: " << tcp.dst_port << "\n"
           << "Seq: " << tcp.seq_n << "\n"
           << "Ack: " << tcp.ack_n << "\n"
           << "Header length: " << (tcp.offset >> 4) << "\n"
           << "Flags: " <<
              ((tcp.flags & 0x1) ? "FIN " : "") <<
              ((tcp.flags & 0x2) ? "SYN " : "") <<
              ((tcp.flags & 0x4) ? "RST " : "") <<
              ((tcp.flags & 0x8) ? "PSH " : "") <<
              ((tcp.flags & 0x10) ? "ACK " : "") <<
              ((tcp.flags & 0x20) ? "URG " : "") <<
              ((tcp.flags & 0x40) ? "ECE " : "") <<
              ((tcp.flags & 0x80) ? "CWR " : "") << "\n"
           << "Window size: " << tcp.win << "\n"
           << "CRC: " << QString("0x%1").arg(tcp.crc, 0, 16) << "\n"
           << "Padding: " << tcp.padding << "\n";
    stream.flush();
}

const QString& TCPHeaderFormatter::GetString() const
{
    return str_;
}
