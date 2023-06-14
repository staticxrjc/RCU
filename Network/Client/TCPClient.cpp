#include "TCPClient.h"

namespace RCU {

TCPClient::TCPClient(const char* ipAddress, int port, const char* name) : 
    BaseClient(ipAddress, port, name) { 
        printf("Establishing Client [%s]\n",name);
    }

RCU::NetworkStatus TCPClient::send(std::string_view sendbuf) {
    if(_connectSocket->send(std::string(sendbuf).c_str()) != RCU::NetworkStatus::SUCCESS) {
        printf("FAILED TO SEND\n");
        return RCU::NetworkStatus::SEND_FAILURE;
    }
    printf("SENT DATA\n");
    return RCU::NetworkStatus::SUCCESS;
}

std::string TCPClient::recv() {
    if(_connectSocket->recv() != RCU::NetworkStatus::SUCCESS) {
        printf("FAILED TO RECV\n");
        return "";
    }
    else
        return _connectSocket->getRecvMessage();
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
    printf("CONNECTED\n");
    return RCU::NetworkStatus::SUCCESS;
}

}