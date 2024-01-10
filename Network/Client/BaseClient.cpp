#include "BaseClient.h"

namespace RCU {

BaseClient::BaseClient(const char* ipAddress, int port, const char* name) {
    _name = name;
    _connectSocket = std::make_unique<ConnectSocket>(
        AF_INET,
        SOCK_STREAM,
        IPPROTO_TCP,
        port,
        INADDR_ANY,
        ipAddress
    );
}

BaseClient::~BaseClient() {
    printf("Destroying ISocket\n");
    _connectSocket.reset();
}

RCU::NetworkStatus BaseClient::init() {
    if(_connectSocket->init() != RCU::NetworkStatus::SUCCESS) {
        return RCU::NetworkStatus::INIT_FAILURE;
    };
    return RCU::NetworkStatus::SUCCESS;

}

}