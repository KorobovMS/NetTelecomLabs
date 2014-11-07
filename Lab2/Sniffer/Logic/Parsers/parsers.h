#ifndef PARSERS_H
#define PARSERS_H

#include "ippacket.h"
#include "icmpsegment.h"
#include "udpsegment.h"
#include "tcpsegment.h"

/**
 * @brief ParseIP parses IP packet from byte array
 */
IPPacket ParseIP(const QByteArray& bytes);

/**
 * @brief ParseICMP parses ICMP segment from byte array
 */
ICMPSegment ParseICMP(const QByteArray& bytes);

/**
 * @brief ParseUDP parses UDP segment from byte array
 */
UDPSegment ParseUDP(const QByteArray& bytes);

/**
 * @brief ParseTCP parses TCP segment from byte array
 */
TCPSegment ParseTCP(const QByteArray& bytes);

#endif // PARSERS_H
