#include "BaseServer.h"

namespace RCU {
    BaseServer::BaseServer(int port, const char* name, int buffer) {
        _name = name;
        _listenSocket = std::make_unique<ListenSocket>(
            AF_INET,
            SOCK_STREAM,
            IPPROTO_TCP,
            port,
            INADDR_ANY,
            buffer
        );
    }

    RCU::NetworkStatus BaseServer::init() {
        if(_listenSocket->init() != 0) {
            return RCU::NetworkStatus::INIT_FAILURE;
        };
        return RCU::NetworkStatus::SUCCESS;
    }

    void BaseServer::start() {
        _running = true;
        while (_running) {
            _acceptor();
        }
    }

    void BaseServer::_handleAccept(RCU::Network client) {
        std::shared_ptr<RCU::Network> lClient = std::make_shared<RCU::Network>(std::move(client));
        _handler(lClient);
        _responder(lClient);
    }

    void BaseServer::stop() {
        _running = false;
    }

    const char* BaseServer::getName() { return _name; }
}