#ifndef IP_HEADER_H
#define IP_HEADER_H

#include <qglobal.h>
#include <QByteArray>

/**
 * Supported protocols. See list of IP protocol numbers
 */
namespace Protocols
{
const quint8 ICMP = 0x01;
const quint8 TCP = 0x06;
const quint8 UDP = 0x11;
}

/**
 * @brief The IPPacket struct contains header and data sections of IP packet
 */
struct IPPacket
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
    QByteArray data; // IP data
};

#endif // IP_HEADER_H
