#ifndef PARSERS_H
#define PARSERS_H

#include "ippacket.h"
#include "icmpsegment.h"
#include "udpsegment.h"
#include "tcpsegment.h"

IPPacket ParseIP(const QByteArray& bytes);
ICMPSegment ParseICMP(const QByteArray& bytes);
UDPSegment ParseUDP(const QByteArray& bytes);
TCPSegment ParseTCP(const QByteArray& bytes);

#endif // PARSERS_H
