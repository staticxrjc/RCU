#include "Graylog.h" 

namespace RCU
{
    
Graylog::Graylog(const char *ip, unsigned short port, const std::string &serviceName) : LogTransport() { 
    _ip = ip;
    _serviceName = serviceName;
    _port = port;
    _logServer = std::make_unique<RCU::TCPClient>(_ip,_port,_serviceName.c_str());
}

Graylog::~Graylog() {
    printf("Destroying Graylog\n");
    _logServer.reset();
}

RCU::LogStatus Graylog::sendLog(RCU::LogType level, std::string_view message, std::string_view fullMessage)
{
    if(!getStatus()) return RCU::LogStatus::DISABLED;
    std::string epochTime = std::to_string (_getTimeMs());
    epochTime.erase ( epochTime.find_last_not_of('0') + 1, std::string::npos );
    epochTime.erase ( epochTime.find_last_not_of('.') + 1, std::string::npos );

    {
        std::unique_lock lock(_mutex);
        if(_logServer->connect() != RCU::NetworkStatus::SUCCESS) {
            disable();
            _logServer->close();
            return RCU::LogStatus::FAILED_NETWORK;
        }
        _logServer->send("{\
    \"version\": \"1.1\",\
    \"host\": \""  + std::string(_serviceName) + "\",\
    \"short_message\": \"" + std::string(message) + "\",\
    \"full_message\": \"" + std::string(fullMessage) + "\",\
    \"timestamp\": " + epochTime + ",\
    \"level\": " + std::to_string(static_cast<int>(level)) + ",\
    \"service\": \""  + std::string(_serviceName) + "\"\
}\0");
        _logServer->close();
    }
    return RCU::LogStatus::SUCCESS;
}

} // namespace RCU
