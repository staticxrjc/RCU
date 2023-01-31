#ifndef BASECLIENT_H
#define BASECLIENT_H

#include "../Sockets/ConnectSocket.h"

namespace RCU {

class BaseClient {
protected:
    int init();
    const char* _name;
    std::unique_ptr<ConnectSocket> _connectSocket;

public:
    BaseClient(const char *ipAddress, int port, const char* name);

};

}

#endif // BASECLIENT_H