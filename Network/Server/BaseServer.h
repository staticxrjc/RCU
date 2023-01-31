#ifndef BASESERVER_H
#define BASESERVER_H

#include "../Sockets/ListenSocket.h"
#include "../../Threadpool/ThreadpoolManager.h"

namespace RCU {

class BaseServer {
private:
    bool _running = false;
    const char* _name;

protected:
    ThreadpoolManager threadpool;
    std::unique_ptr<ListenSocket> _listenSocket;
    void _handleAccept(RCU::Network client);
    virtual void _acceptor() = 0;
    virtual void _handler(std::shared_ptr<RCU::Network> client) = 0;
    virtual void _responder(std::shared_ptr<RCU::Network> client) = 0;

public:
    BaseServer(int port, const char* name, int buffer = 100);
    int init();
    /**
     * @brief sends callback, passes recv into callback
     * 
     * @param callback 
     */
    virtual void start();
    void stop();
    const char* getName();
};

}
#endif // BASESERVER_H