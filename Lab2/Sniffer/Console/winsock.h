#ifndef WINSOCK_H
#define WINSOCK_H

/**
 * @brief The WinSock class initializes Windows Socket library
 */
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
