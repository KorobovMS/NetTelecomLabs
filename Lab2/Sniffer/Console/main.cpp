#include <QCoreApplication>
#include <conio.h>
#include <cstring>

#include <winsock2.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    const int major_version = 2;
    const int minor_version = 2;
    WSADATA wsadata;
    if (WSAStartup(MAKEWORD(major_version, minor_version), &wsadata))
    {
        return WSAGetLastError();
    }

    if (LOBYTE(wsadata.wVersion) != minor_version ||
            HIBYTE(wsadata.wVersion) != major_version)
    {
        return WSAGetLastError();
    }

    char name[128];
    if (gethostname(name, sizeof(name)))
    {
        WSACleanup();
        return WSAGetLastError();
    }

    HOSTENT* he = gethostbyname(name);

    SOCKADDR_IN sa;
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = ((struct in_addr*)he->h_addr_list[0])->s_addr;

    SOCKET s = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
    if (s == INVALID_SOCKET)
    {
        WSACleanup();
        return WSAGetLastError();
    }
    if (bind(s, (SOCKADDR*)&sa, sizeof(SOCKADDR)))
    {
        closesocket(s);
        WSACleanup();
        return WSAGetLastError();
    }

    unsigned long flag = 1;
    if (ioctlsocket(s, 0x98000001, &flag))
    {
        closesocket(s);
        WSACleanup();
        return WSAGetLastError();
    }

    const int SIZE = 0x10000;
    char* buffer = new char[SIZE];
    while (!kbhit())
    {
        int count = recv(s, buffer, SIZE, 0);
        printf("IP %d\n", count);
    }
    delete buffer;

    closesocket(s);
    WSACleanup();

    return 0;
}
