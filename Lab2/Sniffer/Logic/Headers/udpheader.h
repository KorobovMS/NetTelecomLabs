#ifndef UDPHEADER_H
#define UDPHEADER_H

#include <qglobal.h>

struct UDPHeader
{
    quint16 src_port; // source port
    quint16 dst_port; // destination port
    quint16 length; // datagram length
    quint16 crc; // header's CRC
};

#endif // UDPHEADER_H
