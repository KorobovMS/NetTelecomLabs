#include "listener.h"

Listener::Listener() :
    is_good_(false),
    data_size_(0x10000),
    data_(0)
{
}

bool Listener::Initialize()
{
    if (is_good_)
    {
        return true;
    }

    char name[128];
    if (gethostname(name, sizeof(name)))
    {
        return false;
    }

    HOSTENT* he = gethostbyname(name);

    SOCKADDR_IN sa;
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = ((struct in_addr*)he->h_addr_list[0])->s_addr;

    socket_ = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
    if (socket_ == INVALID_SOCKET)
    {
        return false;
    }
    if (bind(socket_, (SOCKADDR*)&sa, sizeof(SOCKADDR)))
    {
        closesocket(socket_);
        return false;
    }

    unsigned long flag = 1;
    const long RECEIVE_ALL_PACKETS = 0x98000001;
    if (ioctlsocket(socket_, RECEIVE_ALL_PACKETS, &flag))
    {
        closesocket(socket_);
        return false;
    }

    data_ = new char[data_size_];

    is_good_ = true;
    return true;
}

QByteArray Listener::Receive()
{
    if (!is_good_)
    {
        return QByteArray();
    }

    int count = recv(socket_, data_, data_size_, 0);
    if (count > 0)
    {
        return QByteArray(data_, count);
    }
    else
    {
        return QByteArray();
    }
}

Listener::~Listener()
{
    if (is_good_)
    {
        delete data_;
        closesocket(socket_);
    }
}
