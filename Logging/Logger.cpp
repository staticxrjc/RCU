#include "Logger.h"

namespace RCU 
{

Logger::Logger() { 
    _threadpool.Start();
}

void Logger::_sendLogs(RCU::LogType level, const char* message) {
    for(auto &transport : _transport) {
        _threadpool.QueueJob([&transport,level,message](){transport->sendLog(level,message);});
    }
}

void Logger::fatal(const char *message)
{
    _sendLogs(RCU::LogType::FATAL,message);
}

void Logger::error(const char *message)
{
    _sendLogs(RCU::LogType::ERR,message);
}

void Logger::warning(const char *message)
{
    _sendLogs(RCU::LogType::WARNING,message);
}

void Logger::info(const char *message)
{
    _sendLogs(RCU::LogType::INFO,message);
}

void Logger::debug(const char *message)
{
    _sendLogs(RCU::LogType::DEBUG,message);
}

void Logger::addLogger(int flags)
{
    if(flags & RCU::Transports::CONSOLE)
        _transport.emplace_back(std::make_unique<RCU::Console>());
    if(flags & RCU::Transports::GRAYLOG)
        std::cout << "GRAYLOG\n";
    if(flags & RCU::Transports::OTHER)
        std::cout << "OTHER\n";
    if(flags & RCU::Transports::FILE)
        std::cout << "FILE\n";
}

void Logger::addLogger(RCU::Transports flag)
{
    addLogger(static_cast<int>(flag));
}

}