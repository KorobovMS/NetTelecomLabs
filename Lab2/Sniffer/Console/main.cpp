#include <conio.h>
#include <cstring>
#include <cstdio>

#include <QHostAddress>

#include "listener.h"
#include "parsers.h"
#include "winsock.h"
#include "datagramprocessor.h"

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

    DatagramProcessor processor;
    while (!kbhit())
    {
        QByteArray datagram = listener.Receive();
        processor.Process(datagram);
    }

    return 0;
}
