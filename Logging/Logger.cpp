#include "Logger.h"

static RCU::AllocationMetrics metrics;

void * operator new(size_t size)
{
    metrics.totalAllocated += size;
    return malloc(size);
}
void operator delete(void * p, size_t size)
{
    metrics.totalFreed += size;
    free(p);
}

namespace RCU 
{

Logger::Logger() { 
    _threadpool.Start();
}

Logger::~Logger(){
    _threadpool.Stop();
}

void Logger::_sendLogs(RCU::LogType level, const std::string& message, const std::string& fullMessage) {
    for(auto &transport : _transport) 
        _threadpool.QueueJob([&transport,level,message,fullMessage](){
            transport->sendLog(level,message,fullMessage.empty() ? message : fullMessage);
        });
}

void Logger::fatal(const std::string &message, const std::string &fullMessage)
{
    _sendLogs(RCU::LogType::FATAL,message,fullMessage);
}

void Logger::error(const std::string &message, const std::string &fullMessage)
{
    _sendLogs(RCU::LogType::ERR,message,fullMessage);
}

void Logger::warning(const std::string &message, const std::string &fullMessage)
{
    _sendLogs(RCU::LogType::WARNING,message,fullMessage);
}

void Logger::info(const std::string &message, const std::string &fullMessage)
{
    _sendLogs(RCU::LogType::INFO,message,fullMessage);
}

void Logger::debug(const std::string &message, const std::string &fullMessage)
{
    _sendLogs(RCU::LogType::DEBUG,message,fullMessage);
}

uint32_t AllocationMetrics::currentUsage() {
    return totalAllocated - totalFreed;
}
std::string Logger::Memory() {
    return std::to_string(metrics.currentUsage());
}

}