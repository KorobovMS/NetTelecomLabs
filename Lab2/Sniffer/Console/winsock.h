#ifndef WINSOCK_H
#define WINSOCK_H

class WinSock
{
public:
    WinSock();
    bool IsInitialized() const;
    ~WinSock();

private:
    bool is_initialized_;
};

#endif // WINSOCK_H
