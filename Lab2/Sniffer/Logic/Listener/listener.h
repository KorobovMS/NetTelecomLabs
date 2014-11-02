#ifndef LISTENER_H
#define LISTENER_H

#include <winsock2.h>

#include <QByteArray>

class Listener
{
public:
    Listener();
    bool Initialize();
    QByteArray Receive();
    ~Listener();

private:
    bool is_good_;
    SOCKET socket_;
    const int data_size_;
    char* data_;
};

#endif // LISTENER_H
