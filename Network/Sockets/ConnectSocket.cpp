#include "ConnectSocket.h"

namespace RCU {

ConnectSocket::ConnectSocket(int domain, int service, int protocol, u_short port, u_long iface, const char* ipAddress) :
    BaseSocket(domain, service, protocol, port, iface) { 
        #if defined(_WIN32) || defined(_WIN64)
            _address.sin_addr.S_un.S_addr = inet_addr(ipAddress);
        #endif // WINDOWS
        #if defined(__linux__) || defined(_unix_)
            if(inet_pton(AF_INET, ipAddress, &_address.sin_addr)<0)
                _addressResult = RCU::NetworkStatus::BAD_IP;
            else
                _addressResult = RCU::NetworkStatus::SUCCESS;

        #endif // LINUX
    }

RCU::NetworkStatus ConnectSocket::_connectToPeer() {
    return RCU::NetworkStatus::SUCCESS;
}

RCU::NetworkStatus ConnectSocket::connect() {
    if(!_initialized)
        return RCU::NetworkStatus::NOT_INITIALIZED;
    #if defined(__linux__) || defined(_unix_)
        if(_addressResult == RCU::NetworkStatus::BAD_IP)
            return _addressResult;
        int result = ::connect(_sock.Socket, (struct sockaddr*)&_address, sizeof(_address));
        if(result < 0)
            return RCU::NetworkStatus::CONNECT_ERROR;
    #endif // LINUX
    #if defined(_WIN32) || defined(_WIN64)
        // Attempt to connect to an address until one succeeds
        for(_ptr=_result; _ptr != NULL ;_ptr=_ptr->ai_next) {

            // Connect to server.
            int result = ::connect( _sock.Socket, (sockaddr*)&_address, sizeof(_address));
            if (result == SOCKET_ERROR) {
                closesocket(_sock.Socket);
                _sock.Socket = INVALID_SOCKET;
                continue;
            }
            break;
        }

        if(_sock.Socket == INVALID_SOCKET) {
            printf("Unable to connect to server!\n");
            WSACleanup();
            _initialized = false;
            return RCU::NetworkStatus::CONNECT_ERROR;
        }
    #endif // WINDOWS
    return RCU::NetworkStatus::SUCCESS;
}

RCU::NetworkStatus ConnectSocket::send(const char * sendbuf) {
    if(!_initialized) {
        printf("Not Initialized!\n");
        return RCU::NetworkStatus::NOT_INITIALIZED;
    }
    #if defined(__linux__) || defined(_unix_)
        if(::send(_sock.Socket, sendbuf, strlen(sendbuf) , 0 )<0) {
            printf("send failed\n");
            shutdown(_sock.Socket,SHUT_RDWR);
            ::close(_sock.Socket);
            return RCU::NetworkStatus::FAILURE;
        }
    #endif // LINUX
    #if defined(_WIN32) || defined(_WIN64)
        int result = ::send( _sock.Socket, sendbuf, (int)strlen(sendbuf), 0 );
        if (result == SOCKET_ERROR) {
            printf("send failed with error: %d\n", WSAGetLastError());
            closesocket(_sock.Socket);
            WSACleanup();
            return RCU::NetworkStatus::FAILURE;
        }
    #endif // WINDOWS
    return RCU::NetworkStatus::SUCCESS;
}

RCU::NetworkStatus ConnectSocket::recv() {
    if(!_initialized)
        return RCU::NetworkStatus::NOT_INITIALIZED;
    char buffer[1024];
    _recvMessage = "";

    int nDataLength;
    while ((nDataLength = ::recv(_sock.Socket, buffer, sizeof(buffer), 0)) > 0) {
        _recvMessage.append(buffer, nDataLength);
    }

    return RCU::NetworkStatus::SUCCESS;
}

std::string ConnectSocket::getRecvMessage() {
    return _recvMessage;
}

}