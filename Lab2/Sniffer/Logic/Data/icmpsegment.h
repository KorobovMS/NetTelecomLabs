#ifndef ICMPHEADER_H
#define ICMPHEADER_H

#include <qglobal.h>
#include <QByteArray>

struct ICMPSegment
{
    quint8 type; // ICMP type
    quint8 code; // ICMP code
    quint16 crc; // header's CRC
    QByteArray data; // ICMP data
};

#endif // ICMPHEADER_H
