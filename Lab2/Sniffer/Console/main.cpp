#include <conio.h>
#include <cstring>
#include <cstdio>

#include "winsock.h"
#include "listener.h"

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
        printf("IP %d\n", datagram.size());
    }

    return 0;
}
