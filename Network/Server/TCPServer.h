#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "BaseServer.h"

namespace RCU
{

class TCPServer : public BaseServer {
protected:
    bool _handling = false;
    virtual void _acceptor() override;
    virtual void _handler(std::shared_ptr<RCU::Network> client) override;
    virtual void _responder(std::shared_ptr<RCU::Network> client) override;
public:
    TCPServer(int port, const char* name, int buffer);
    ~TCPServer();
};

}

#endif // TCPSERVER_H