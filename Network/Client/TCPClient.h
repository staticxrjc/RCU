#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "BaseClient.h"

namespace RCU {

class TCPClient : public BaseClient {
public:
    TCPClient(const char* ipAddress, int port, const char* name);
    void send(std::string_view sendbuf);
    std::string recv();
    void close();
    RCU::NetworkStatus connect();
};

}

#endif // TCPCLIENT_H