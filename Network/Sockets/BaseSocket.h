#ifndef BASESOCKET_H
#define BASESOCKET_H
#if defined(_WIN32) || defined(_WIN64)
    #define WIN32_LEAN_AND_MEAN

    #include <windows.h>
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #include <sstream>
    
    // Need to link with Ws2_32.lib
    #pragma comment (lib, "Ws2_32.lib")
    // #pragma comment (lib, "Mswsock.lib")
#endif // WINDOWS

#if defined(linux) || defined(_unix_)
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <string.h>
#endif // LINUX

#include <iostream>

namespace RCU 
{
typedef enum {
    SUCCESS = 0,
    INIT_FAILURE = -1,
    SOCK_INIT_FAIL = -2,
    CONNECT_ERROR = -3,
    EXPANDED_INIT_FAILURE = -4
} RCU_RESULT;

struct Network {
    Network() {
        #if defined(_WIN32) || defined(_WIN64)
            Socket = INVALID_SOCKET;
        #endif // WINDOWS
    }
    #if defined(_WIN32) || defined(_WIN64)
        SOCKET Socket;
    #endif // WINDOWS
    #if defined(linux) || defined(_unix_)
        int Socket;
    #endif // LINUX
};


class BaseSocket {
protected:
    RCU::Network _sock;
    #if defined(_WIN32) || defined(_WIN64)
        WSADATA _wsaData;
        struct addrinfo *_result = NULL;
        struct addrinfo _hints;
    #endif // WINDOWS
    #if defined(linux) || defined(_unix_)
        struct sockaddr_in _address;
    #endif // LINUX

    virtual int _connectToPeer() = 0;

private:
    int _connection;
    int _service;
    int _protocol;
    int _port;

public:
    BaseSocket(int domain, int service, int protocol, int port, u_long iface);
    RCU::Network& getSocket();
    int getConnection();
    int getPort();
    /**
     * @brief Initializes socket
     * 
     * @return int 
     *  0 = success
     *  -1 = failure to initialize
     *  -2 = failure to create socket
     *  -3 = failure to connect/bind
     *  -4 = expanded init failed
     */
    int init();
};

}

#endif // BASESOCKET_H