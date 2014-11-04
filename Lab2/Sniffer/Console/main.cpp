#include <conio.h>
#include <cstring>
#include <cstdio>

#include <QHostAddress>

#include "ippacket.h"
#include "listener.h"
#include "parsers.h"
#include "winsock.h"

int main(int argc, char *argv[])
{
    WinSock ws;
    if (!ws.IsInitialized())
    {
        printf("WinSock cannot be initialized\n");
        return 1;
    }

    Listener listener;
    if (!listener.Initialize())
    {
        printf("Cannot listen to network adapter\n");
        return 2;
    }

    while (!kbhit())
    {
        QByteArray datagram = listener.Receive();
        IPPacket ip = ParseIP(datagram);
        qDebug() << QHostAddress(ip.dst_addr)
                 << ip.proto
                 << QString("%1").arg(ip.flags_fo >> 13, 3, 2, QChar('0'))
                 << ip.tlen;
    }

    return 0;
}
