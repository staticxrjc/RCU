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

#if defined(__linux__) || defined(_unix_)
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <string.h>
    #include <arpa/inet.h>
    #include <unistd.h>
#endif // LINUX

#include <iostream>

namespace RCU 
{
enum class NetworkStatus {
    SUCCESS = 0,
    INIT_FAILURE = -1,
    SOCK_INIT_FAIL = -2,
    CONNECT_ERROR = -3,
    SEND_FAILURE = -4,
    BAD_IP = -5,
    FAILURE = -6,
    ALEADY_INITIALIZED = -7,
    NOT_INITIALIZED = -8
};

struct Network {
    Network() {
        #if defined(_WIN32) || defined(_WIN64)
            Socket = INVALID_SOCKET;
        #endif // WINDOWS
    }
    #if defined(_WIN32) || defined(_WIN64)
        SOCKET Socket;
    #endif // WINDOWS
    #if defined(__linux__) || defined(_unix_)
        int Socket;
    #endif // LINUX
};


class BaseSocket {
protected:
    RCU::Network _sock;
    sockaddr_in _address;
    bool _initialized;
    virtual RCU::NetworkStatus _connectToPeer() = 0;

    #if defined(_WIN32) || defined(_WIN64)
        WSADATA _wsaData;
        struct addrinfo *_result = NULL;
        struct addrinfo *_ptr = NULL;
        struct addrinfo _hints;
    #endif // WINDOWS


private:
    RCU::NetworkStatus _connection;
    int _service;
    int _protocol;
    u_short _port;

public:
    BaseSocket(int domain, int service, int protocol, u_short port, u_long iface);
    RCU::Network& getSocket();
    RCU::NetworkStatus getConnection();
    u_short getPort();
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
    RCU::NetworkStatus init();
    virtual RCU::NetworkStatus close();
};

}

#endif // BASESOCKET_H