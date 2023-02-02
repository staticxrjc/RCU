#ifndef CONNECTSOCKET_H
#define CONNECTSOCKET_H

#include "BaseSocket.h"

namespace RCU {

class ConnectSocket : public BaseSocket {
private:
    RCU::NetworkStatus _connectToPeer() override;
    std::string _recvMessage;

public:
    ConnectSocket(int domain, int service, int protocol, u_short port, u_long iface, const char* ipAddress);
    RCU::NetworkStatus connect();
    RCU::NetworkStatus send(const char * message);
    RCU::NetworkStatus recv();
    std::string getRecvMessage();
};

}
#endif //CONNECTSOCKET_H