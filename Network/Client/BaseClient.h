#ifndef BASECLIENT_H
#define BASECLIENT_H

#include "../Sockets/ConnectSocket.h"
#include <memory>

namespace RCU {

class BaseClient {
protected:
    RCU::NetworkStatus init();
    const char* _name;
    std::unique_ptr<RCU::ConnectSocket> _connectSocket;

public:
    BaseClient(const char *ipAddress, int port, const char* name);
    virtual ~BaseClient();
};

}

#endif // BASECLIENT_H