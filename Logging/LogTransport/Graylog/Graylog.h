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
    std::string _serviceName;
    unsigned short _port;

public:
    Graylog(const char* ip, unsigned short port, const std::string &serviceName);
    ~Graylog();
    RCU::LogStatus sendLog(RCU::LogType LogType, std::string_view message, std::string_view fullMessage) override;

};
    
} // namespace RCU


#endif