#include "winsock.h"

#include <winsock2.h>

WinSock::WinSock() :
    is_initialized_(false)
{
    const int major_version = 2;
    const int minor_version = 2;
    WSADATA wsadata;
    if (WSAStartup(MAKEWORD(major_version, minor_version), &wsadata))
    {
        return;
    }

    if (LOBYTE(wsadata.wVersion) != minor_version ||
            HIBYTE(wsadata.wVersion) != major_version)
    {
        return;
    }

    is_initialized_ = true;
}

bool WinSock::IsInitialized() const
{
    return is_initialized_;
}

WinSock::~WinSock()
{
    if (is_initialized_)
    {
        WSACleanup();
    }
}
