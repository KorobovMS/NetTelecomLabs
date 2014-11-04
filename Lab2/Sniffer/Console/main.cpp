#include <conio.h>
#include <cstdio>

#include "listener.h"
#include "winsock.h"
#include "datagramprocessor.h"

int main()
{
    DatagramProcessor processor;
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
        processor.Process(datagram);
    }

    return 0;
}
