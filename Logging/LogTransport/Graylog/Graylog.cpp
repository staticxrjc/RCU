#include "Graylog.h" 

namespace RCU
{
    
Graylog::Graylog(const char *ip, unsigned short port, const char* serviceName) : LogTransport() { 
    _ip = ip;
    _serviceName = serviceName;
    _port = port;
    _logServer = std::make_unique<RCU::TCPClient>(_ip,_port,_serviceName);
}

RCU::LogStatus Graylog::sendLog(RCU::LogType level, const char *message, const char* fullMessage)
{
    std::string epochTime = std::to_string (_getTimeMs());
    epochTime.erase ( epochTime.find_last_not_of('0') + 1, std::string::npos );
    epochTime.erase ( epochTime.find_last_not_of('.') + 1, std::string::npos );

    std::string payload = "{\r\n\
    \"short_message\": \"" + std::string(message) + "\",\r\n\
    \"full_message\": \"" + std::string(fullMessage) + "\",\r\n\
    \"timestamp\": " + epochTime + ",\r\n\
    \"level\": " + std::to_string(static_cast<int>(level)) + ",\r\n\
    \"service\": \""  + std::string(_serviceName) + "\"\r\n\
}\r\n";
    {
        std::unique_lock lock(_mutex);
        _logServer->connect();
        _logServer->send(payload.c_str());
        _logServer->close();
    }
    return RCU::LogStatus::SUCCESS;
}

} // namespace RCU
