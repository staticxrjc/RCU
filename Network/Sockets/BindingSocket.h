#ifndef BINDINGSOCKET_H
#define BINDINGSOCKET_H
#include "BaseSocket.h"
#include <string>

namespace RCU 
{

class BindingSocket : public BaseSocket 
{
private:
    int _backlog;
    int _connectToPeer() override;

public:
    BindingSocket(int domain, int service, int protocol, int port, u_long iface, int backlog);
};

}

#endif // BINDINGSOCKET_H