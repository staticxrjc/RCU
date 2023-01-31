#include "ConnectSocket.h"

namespace RCU {

ConnectSocket::ConnectSocket(int domain, int service, int protocol, u_short port, u_long iface, const char* ipAddress) :
    BaseSocket(domain, service, protocol, port, iface) { 
        _address.sin_addr.S_un.S_addr = inet_addr(ipAddress);
    }

int ConnectSocket::_connectToPeer() {
    return RCU::SUCCESS;
}

int ConnectSocket::connect() {
    if(!_initialized)
        return RCU::NOT_INITIALIZED;
    printf("Connecting to Peer\n");
    #if defined(linux) || defined(_unix_)
        int result = ::connect(_sock.Socket, (struct sockaddr*)&_address, sizeof(_address));
        return result;
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
            return RCU::CONNECT_ERROR;
        }

        printf("Successfully Created Client.\n");
        return RCU_RESULT::SUCCESS;
    #endif // WINDOWS
}

int ConnectSocket::send(const char * sendbuf) {
    if(!_initialized)
        return RCU::NOT_INITIALIZED;
    printf("SEND: %s", sendbuf);
    int result = ::send( _sock.Socket, sendbuf, (int)strlen(sendbuf), 0 );
    if (result == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(_sock.Socket);
        WSACleanup();
        return RCU::FAILURE;
    }
    return RCU::SUCCESS;
}

int ConnectSocket::recv() {
    if(!_initialized)
        return RCU::NOT_INITIALIZED;
    char buffer[1024];
    _recvMessage = "";

    int nDataLength;
    while ((nDataLength = ::recv(_sock.Socket, buffer, sizeof(buffer), 0)) > 0) {
        _recvMessage.append(buffer, nDataLength);
    }

    std::cout << "RECV: " << _recvMessage << "\n"; 
    return SUCCESS;
}

}