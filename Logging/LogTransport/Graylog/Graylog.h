#ifndef GRAYLOG_H
#define GRAYLOG_H

#include "../LogTransport.h"
#include "../../../Network/Client/TCPClient.h"

namespace RCU
{

class Graylog : public LogTransport {
private:
    std::unique_ptr<RCU::TCPClient> _logServer;
    const char* _ip;
    const char* _serviceName;
    unsigned short _port;

public:
    Graylog(const char* ip, unsigned short port, const char* serviceName);
    RCU::LogStatus sendLog(RCU::LogType LogType, const char* message, const char* fullMessage) override;

};
    
} // namespace RCU


#endif