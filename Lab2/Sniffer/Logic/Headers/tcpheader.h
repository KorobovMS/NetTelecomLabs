#ifndef TCPHEADER_H
#define TCPHEADER_H

#include <qglobal.h>

struct TCPHeader
{
    quint16 src_port; // source port
    quint16 dst_port; // destination port
    quint32 seq_n; // sequence number
    quint32 ack_n; // acknowledgement number
    quint8 offset; // header length (4 bit) + reserved (4 bit)
    quint8 flags; // reserved (2 bit) + flags (6 bit)
    quint16 win; // window size
    quint16 crc; // header's CRC
    quint16 padding; // urgent pointer
};

#endif // TCPHEADER_H
