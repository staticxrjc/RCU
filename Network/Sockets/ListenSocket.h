#ifndef LISTENSOCKET_H
#define LISTENSOCKET_H
#include "BindingSocket.h"
#include <memory>
#include <string>

namespace RCU 
{

class ListenSocket : public BindingSocket 
{
private:
    int _backlog;
    std::shared_ptr<RCU::Network> _client;

public:
    ListenSocket(int domain, int service, int protocol, int port, u_long iface, int backlog);
    int init();
    std::shared_ptr<RCU::Network> acceptConnection();
};

}

#endif // LISTENSOCKET_H