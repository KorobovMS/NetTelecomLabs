#ifndef ICMPHEADER_H
#define ICMPHEADER_H

#include <qglobal.h>

struct ICMPHeader
{
    quint8 type; // ICMP type
    quint8 code; // ICMP code
    quint16 crc; // header's CRC
};

#endif // ICMPHEADER_H
