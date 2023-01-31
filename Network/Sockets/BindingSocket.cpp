#include "BindingSocket.h"

namespace RCU
{

BindingSocket::BindingSocket(int domain, int service, int protocol, u_short port, u_long iface, int backlog) : 
    BaseSocket(domain, service, protocol, port, iface) { }

int BindingSocket::_connectToPeer() {
    #if defined(linux) || defined(_unix_)
        int result = bind(_sock.Socket, (struct sockaddr*)&_address, sizeof(_address));
        return result;
    #endif // LINUX
    #if defined(_WIN32) || defined(_WIN64)
        int result = bind( _sock.Socket, _result->ai_addr, (int)_result->ai_addrlen);
        if (result == SOCKET_ERROR) {
            printf("bind failed with error: %ld\n", WSAGetLastError());
            freeaddrinfo(_result);
            closesocket(_sock.Socket);
            WSACleanup();
            return RCU::FAILURE;
        }
        return RCU::SUCCESS;
    #endif // WINDOWS
}

}