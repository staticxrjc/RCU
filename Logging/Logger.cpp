#include "Logger.h"

namespace RCU 
{

Logger::Logger() { 
    _threadpool.Start();
}

Logger::~Logger(){
    _threadpool.Stop();
}

void Logger::_sendLogs(RCU::LogType level, const char* message, const char* fullMessage) {
    if (fullMessage == nullptr)
        fullMessage = message;
    for(auto &transport : _transport) {
        _threadpool.QueueJob([&transport,level,message,fullMessage](){transport->sendLog(level,message,fullMessage);});
    }
}

void Logger::fatal(const char *message, const char *fullMessage)
{
    _sendLogs(RCU::LogType::FATAL,message,fullMessage);
}

void Logger::error(const char *message, const char *fullMessage)
{
    _sendLogs(RCU::LogType::ERR,message,fullMessage);
}

void Logger::warning(const char *message, const char *fullMessage)
{
    _sendLogs(RCU::LogType::WARNING,message,fullMessage);
}

void Logger::info(const char *message, const char *fullMessage)
{
    _sendLogs(RCU::LogType::INFO,message,fullMessage);
}

void Logger::debug(const char *message, const char *fullMessage)
{
    _sendLogs(RCU::LogType::DEBUG,message,fullMessage);
}

}