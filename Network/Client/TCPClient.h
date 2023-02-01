#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "BaseClient.h"

namespace RCU {

class TCPClient : public BaseClient {
public:
    TCPClient(const char* ipAddress, int port, const char* name);
    void send(const char* sendbuf);
    void recv();
    void close();
    RCU::NetworkStatus connect();
};

}

#endif // TCPCLIENT_H