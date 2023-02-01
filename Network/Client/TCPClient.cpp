#include "TCPClient.h"

namespace RCU {

TCPClient::TCPClient(const char* ipAddress, int port, const char* name) : 
    BaseClient(ipAddress, port, name) { 
        printf("Establishing Client [%s]\n",name);
    }

void TCPClient::send(const char* sendbuf) {
    if(_connectSocket->send(sendbuf) != RCU::NetworkStatus::SUCCESS)
        printf("FAILED TO SEND\n");
}

void TCPClient::recv() {
    if(_connectSocket->recv() != RCU::NetworkStatus::SUCCESS)
        printf("FAILED TO RECV\n");
}

void TCPClient::close(){
    _connectSocket->close();
}

RCU::NetworkStatus TCPClient::connect() {
    init();
    if(_connectSocket->connect() != RCU::NetworkStatus::SUCCESS) {
        printf("CONNECT FAILED\n");
        return RCU::NetworkStatus::CONNECT_ERROR;
    }
    return RCU::NetworkStatus::SUCCESS;
}

}