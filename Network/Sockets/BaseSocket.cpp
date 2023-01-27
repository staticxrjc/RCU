#include "BaseSocket.h"

namespace RCU 
{
    BaseSocket::BaseSocket(int domain, int service, int protocol, int port, u_long iface) {
        _service = service;
        _protocol = protocol;
        _port = port;
        #if defined(linux) || defined(_unix_)
            // Define Address Structure
            _address.sin_family = domain;
            _address.sin_port = htons(port);
            _address.sin_addr.s_addr = htonl(iface);
            memset(_address.sin_zero, '\0', sizeof _address.sin_zero);
        #endif // LINUX
        #if defined(_WIN32) || defined(_WIN64)
            ZeroMemory(&_hints, sizeof(_hints));
            _hints.ai_family = domain;
            _hints.ai_socktype = service;
            _hints.ai_protocol = protocol;
            _hints.ai_flags = AI_PASSIVE;
        #endif // WINDOWS
    }

    int BaseSocket::init() {
        #if defined(_WIN32) || defined(_WIN64)
            int result = WSAStartup(MAKEWORD(2,2),&_wsaData);
            if(result != 0) {
                std::cout << "WSAStartup failed" << std::endl;
                return INIT_FAILURE;
            }
            std::ostringstream oss;
            oss << _port;
            result = getaddrinfo(NULL, oss.str().c_str(), &_hints, &_result);
            if ( result != 0 ) {
                printf("getaddrinfo failed");
                WSACleanup();
                return INIT_FAILURE;
            }
            _sock.Socket = socket(_result->ai_family, _result->ai_socktype, _result->ai_protocol);
            if(_sock.Socket == INVALID_SOCKET) {
                std::cout << "Failed to create socket" << std::endl;
                return SOCK_INIT_FAIL;
            }
        #endif // WINDOWS
        #if defined(linux) || defined(_unix_)
            // Establish Socket
            _sock = socket(_address.sin_family, _service, _protocol);
            if(_sock == 0) {
                std::cout << "Failed to create socket" << std::endl;
                return SOCK_INIT_FAIL;
            }
        #endif // LINUX
        _connection = _connectToPeer();
        if(_connection < 0) {
            std::cout << "Failed to establish bind/connect" << std::endl;
            return CONNECT_ERROR; 
        }
        return SUCCESS;
    }


    RCU::Network& BaseSocket::getSocket() { return _sock; }
    int BaseSocket::getConnection() { return _connection; }
    int BaseSocket::getPort() { return _port; }
}