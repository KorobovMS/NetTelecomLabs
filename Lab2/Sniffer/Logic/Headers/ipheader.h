#ifndef IP_HEADER_H
#define IP_HEADER_H

#include <qglobal.h>

struct IPHeader
{
    quint8 ver_ihl; // version + internet header length
    quint8 tos; // diff services code point + explicit congestion notification
    quint16 tlen; // packet length
    quint16 id; // packet identifier
    quint16 flags_fo; // flags + fragment's shift
    quint8 ttl; // time to live
    quint8 proto; // high level protocol
    quint16 crc; // header's CRC
    quint32 src_addr; // source address
    quint32 dst_addr; // destination address
};

#endif // IP_HEADER_H
