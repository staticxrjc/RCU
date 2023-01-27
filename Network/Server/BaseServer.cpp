#include "BaseServer.h"

namespace RCU {
    BaseServer::BaseServer(int port, const char* name, int buffer) {
        _listenSocket = std::make_unique<ListenSocket>(
            AF_INET,
            SOCK_STREAM,
            IPPROTO_TCP,
            port,
            INADDR_ANY,
            buffer
        );
    }

    int BaseServer::init() {
        if(_listenSocket->init() != 0) {
            return INIT_FAILURE;
        };
        return 0;
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
}