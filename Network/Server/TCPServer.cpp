#include "TCPServer.h"
#include <thread>

namespace RCU {
    TCPServer::TCPServer(int port, const char* name, int buffer) :
        BaseServer(port, name, buffer) {
            threadpool.Start();
        }

    TCPServer::~TCPServer() {
        threadpool.Stop();
    }

    void TCPServer::_acceptor() {
        std::cout << "Accepting on host [" << getName() << "]" <<std::endl;
        RCU::Network client;
        client.Socket = _listenSocket->acceptConnection()->Socket;
        threadpool.QueueJob([=](){_handleAccept(client);});
    }

    void TCPServer::_handler(std::shared_ptr<RCU::Network> client) {
        std::cout << "Handling" << std::endl;
        std::cout << "Client Socket: " << client->Socket << std::endl;
        int result;
        const int MAX_HTTP_HEADER_SIZE = 1024;
        const char* delimiter = "\n";
        const int _recvbuflen = 256;
        char httpHeader[MAX_HTTP_HEADER_SIZE] = "";
        char _recvbuf[_recvbuflen] = "";

        int byteRecv = 0;
        // Receive until the peer shuts down the connection

        do {
            result = recv(client->Socket, _recvbuf, _recvbuflen, 0);
            if (result > 0) {
                byteRecv += result;
                if(result != _recvbuflen)
                    _recvbuf[result] = '\0';
                if (byteRecv < MAX_HTTP_HEADER_SIZE) // Protects from overflowing
                    strncat(httpHeader, _recvbuf, sizeof(httpHeader) - strlen(httpHeader) - 1);
                else {
                    printf("Header Limit Reached\n");
                }
            }
        } while (!strstr(httpHeader,delimiter));

        std::cout << httpHeader << std::endl;
    }

    void TCPServer::_responder(std::shared_ptr<RCU::Network> client) {
        std::cout << "Responding" << std::endl;
        std::cout << "Client Socket: " << client->Socket << std::endl;
        int result;
        result = send(client->Socket,"Hello\r\n",(int)strlen("Hello\r\n"),0);
        #if defined(_WIN32) || defined(_WIN64)
            if (result == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                shutdown(client->Socket, SD_SEND);
                closesocket(client->Socket);
                WSACleanup();
            return;
            }
        #endif // WINDOWS
        #if defined(linux) || defined(_unix_)
            // TODO linux bad return
        #endif // LINUX

        std::this_thread::sleep_for(std::chrono::seconds(2));

        #if defined(_WIN32) || defined(_WIN64)
            shutdown(client->Socket, SD_SEND);
            closesocket(client->Socket);
        #endif // WINDOWS
        #if defined(linux) || defined(_unix_)
            close(client->Socket);
        #endif // LINUX
    }
}