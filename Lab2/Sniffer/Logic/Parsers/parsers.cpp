#include "parsers.h"

#include <QDataStream>

IPPacket ParseIP(const QByteArray& bytes)
{
    IPPacket ip;
    QDataStream stream(bytes);
    stream >> ip.ver_ihl >> ip.tos >> ip.tlen >> ip.id >> ip.flags_fo >>
            ip.ttl >> ip.proto >> ip.crc >> ip.src_addr >> ip.dst_addr;
    const int header_length = sizeof(IPPacket) - sizeof(IPPacket::data);
    ip.data.resize(bytes.size() - header_length);
    stream.readRawData(ip.data.data(), ip.data.size());
    return ip;
}

ICMPSegment ParseICMP(const QByteArray& bytes)
{
    ICMPSegment icmp;
    QDataStream stream(bytes);
    stream >> icmp.type >> icmp.code >> icmp.crc;
    const int header_length = sizeof(ICMPSegment) - sizeof(ICMPSegment::data);
    icmp.data.resize(bytes.size() - header_length);
    stream.readRawData(icmp.data.data(), icmp.data.size());
    return icmp;
}

UDPSegment ParseUDP(const QByteArray& bytes)
{
    UDPSegment udp;
    QDataStream stream(bytes);
    stream >> udp.src_port >> udp.dst_port >> udp.length >> udp.crc;
    const int header_length = sizeof(UDPSegment) - sizeof(UDPSegment::data);
    udp.data.resize(bytes.size() - header_length);
    stream.readRawData(udp.data.data(), udp.data.size());
    return udp;
}

TCPSegment ParseTCP(const QByteArray& bytes)
{
    TCPSegment tcp;
    QDataStream stream(bytes);
    stream >> tcp.src_port >> tcp.dst_port >> tcp.seq_n >> tcp.ack_n >>
            tcp.offset >> tcp.flags >> tcp.win >> tcp.crc >> tcp.padding;
    const int header_length = sizeof(TCPSegment) - sizeof(TCPSegment::data);
    tcp.data.resize(bytes.size() - header_length);
    stream.readRawData(tcp.data.data(), tcp.data.size());
    return tcp;
}
