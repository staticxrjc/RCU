#include "ListenSocket.h"

namespace RCU 
{
    ListenSocket::ListenSocket(int domain, int service, int protocol, int port, u_long iface, int backlog) :
        BindingSocket(domain, service, protocol, port, iface, backlog) { 
            _client = std::make_shared<RCU::Network>();
        }

    int ListenSocket::init() {
        BaseSocket::init();
        int result = 0;
        #if defined(_WIN32) || defined(_WIN64)
            result = listen(_sock.Socket, SOMAXCONN);
            if(result == SOCKET_ERROR) {
                printf("listen failed with error: %d\n", WSAGetLastError());
                closesocket(_sock.Socket);
                WSACleanup();
                return SOCKET_ERROR;
            }
        #endif // WINDOWS
        #if defined(linux) || defined(_unix_)
            result = listen(_sock.Socket,_backlog);
        #endif // LINUX
        if(result < 0)  return result;
        else {
            std::cout << "Listening on port: " << getPort() << std::endl;
            return 0;
        }
    }

    std::shared_ptr<RCU::Network> ListenSocket::acceptConnection() {
        #if defined(_WIN32) || defined(_WIN64)
            _client->Socket = accept(_sock.Socket, NULL, NULL);
            if (_client->Socket == INVALID_SOCKET) {
                printf("accept failed with error: %d\n", WSAGetLastError());
                closesocket(_sock.Socket);
                WSACleanup();
                return _client;
            }
            return _client;
        #endif // WINDOWS
    }
}