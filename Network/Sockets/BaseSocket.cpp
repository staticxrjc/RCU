#include "BaseSocket.h"

namespace RCU 
{
    BaseSocket::BaseSocket(int domain, int service, int protocol, u_short port, u_long iface) {
        _initialized = false;
        _service = service;
        _protocol = protocol;
        _port = port;
        memset(&_address, '\0', sizeof(_address));
        _address.sin_family = domain;
        _address.sin_port = htons(port);
        _address.sin_addr.s_addr = htonl(iface);

        #if defined(_WIN32) || defined(_WIN64)
            ZeroMemory(&_hints, sizeof(_hints));
            _hints.ai_family = domain;
            _hints.ai_socktype = service;
            _hints.ai_protocol = protocol;
            _hints.ai_flags = AI_PASSIVE;
        #endif // WINDOWS
    }

    RCU::NetworkStatus BaseSocket::init() {
        if(_initialized)
            return RCU::NetworkStatus::INIT_FAILURE;
        #if defined(_WIN32) || defined(_WIN64)
            int result = WSAStartup(MAKEWORD(2,2),&_wsaData);
            if(result != 0) {
                std::cout << "WSAStartup failed" << std::endl;
                return RCU::NetworkStatus::INIT_FAILURE;
            }
            std::ostringstream oss;
            oss << _port;
            result = getaddrinfo(NULL, oss.str().c_str(), &_hints, &_result);
            if ( result != 0 ) {
                printf("getaddrinfo failed");
                WSACleanup();
                return RCU::NetworkStatus::INIT_FAILURE;
            }
            _sock.Socket = socket(_result->ai_family, _result->ai_socktype, _result->ai_protocol);
            if(_sock.Socket == INVALID_SOCKET) {
                std::cout << "Failed to create socket" << std::endl;
                return RCU::NetworkStatus::SOCK_INIT_FAIL;
            }
        #endif // WINDOWS
        #if defined(__linux__) || defined(_unix_)
            // Establish Socket
            _sock.Socket = socket(_address.sin_family, _service, _protocol);
            if(_sock.Socket == 0) {
                std::cout << "Failed to create socket" << std::endl;
                return RCU::NetworkStatus::SOCK_INIT_FAIL;
            }
        #endif // LINUX
        _connection = _connectToPeer();
        if(_connection != RCU::NetworkStatus::SUCCESS) {
            std::cout << "Failed to establish bind/connect" << std::endl;
            return RCU::NetworkStatus::CONNECT_ERROR; 
        }
        _initialized = true;
        return RCU::NetworkStatus::SUCCESS;
    }

    RCU::NetworkStatus BaseSocket::close() {
        if(!_initialized)
            return RCU::NetworkStatus::ALEADY_INITIALIZED;
        #if defined(linux) || defined(_unix_)
        #endif // LINUX
        #if defined(_WIN32) || defined(_WIN64)
            shutdown(_sock.Socket, SD_SEND);
            closesocket(_sock.Socket);
            WSACleanup();
        #endif // WINDOWS
        _initialized = false;
        return RCU::NetworkStatus::SUCCESS;
    }

    RCU::Network& BaseSocket::getSocket() { return _sock; }
    RCU::NetworkStatus BaseSocket::getConnection() { return _connection; }
    u_short BaseSocket::getPort() { return _port; }
}