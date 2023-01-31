#ifndef CONNECTSOCKET_H
#define CONNECTSOCKET_H

#include "BaseSocket.h"

namespace RCU {

class ConnectSocket : public BaseSocket {
private:
    int _connectToPeer() override;
    std::string _recvMessage;

public:
    ConnectSocket(int domain, int service, int protocol, u_short port, u_long iface, const char* ipAddress);
    int connect();
    int send(const char * message);
    int recv();
};

}
#endif //CONNECTSOCKET_H