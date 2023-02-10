#include "Logger.h"

namespace RCU 
{

Logger::Logger() { 
    _threadpool.Start();
}

Logger::~Logger(){
    _threadpool.Stop();
    printf("Destroying Logger\n");
}

void Logger::_sendLogs(RCU::LogType level, const std::string& message, const std::string& fullMessage) {
    {
        std::unique_lock<std::mutex> lock(_mtx);
        for(auto &transport : _transport) 
            _threadpool.QueueJob([&transport,level,message,fullMessage](){
                transport->sendLog(level,message,fullMessage.empty() ? message : fullMessage);
            });
    }
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

void Logger::awaitSendLogs() 
{
    {
        std::unique_lock<std::mutex> lock(_mtx);
        while(_threadpool.Busy())
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

}