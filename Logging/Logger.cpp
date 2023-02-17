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
                if(transport->getStatus())
                    transport->sendLog(level,message,fullMessage.empty() ? message : fullMessage);
            });
    }
}

void Logger::_sendTestResult(RCU::LogType level, const std::string& coded, const std::string& uncoded) {
    {
        std::unique_lock<std::mutex> lock(_mtx);
        for(auto &transport : _transport) 
            _threadpool.QueueJob([&transport,level,coded,uncoded](){
                if(transport->getStatus())
                    if(transport->getColorSupport())
                        transport->sendLog(level,coded,coded);
                    else
                        transport->sendLog(level,uncoded,uncoded);
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

int Logger::test(const std::string &message)
{
    int mapIndex;
    {
        std::unique_lock<std::mutex> lock(_testMtx);
        if(this->_availableMapAddresses.empty()) 
        {
            mapIndex = this->_testMessageContainer.size();
            this->_testMessageContainer[mapIndex] = std::make_pair(message, message);
        }
        else 
        {
            mapIndex = this->_availableMapAddresses.front();
            this->_availableMapAddresses.pop();
            this->_testMessageContainer[mapIndex] = std::make_pair(message, message);
        }
    }
    return mapIndex;
}

void Logger::pass(RCU::LogType level, int reference)
{
    {
        std::unique_lock<std::mutex> lock(_testMtx);
        // append . until string is length 42
        while(this->_testMessageContainer[reference].first.length() < 52) 
        {
            this->_testMessageContainer[reference].first += ".";
            this->_testMessageContainer[reference].second += ".";
        }
        
        this->_testMessageContainer[reference].first += "[";
        this->_testMessageContainer[reference].second += "[";
        this->_testMessageContainer[reference].first += "\033[1;32mPASS\033[0m]";
        this->_testMessageContainer[reference].second += "PASS]";
        
        this->_sendTestResult(
            level, 
            this->_testMessageContainer[reference].first, 
            this->_testMessageContainer[reference].second
        );

        _testMessageContainer.erase(reference);
        _availableMapAddresses.push(reference);
    }
}

void Logger::fail(RCU::LogType level, int reference) 
{
    {
        std::unique_lock<std::mutex> lock(_testMtx);
        // append . until string is length 42
        while(this->_testMessageContainer[reference].first.length() < 52) 
        {
            this->_testMessageContainer[reference].first += ".";
            this->_testMessageContainer[reference].second += ".";
        }
        
        this->_testMessageContainer[reference].first += "[";
        this->_testMessageContainer[reference].second += "[";
        this->_testMessageContainer[reference].first += "\033[1;31mFAIL\033[0m]";
        this->_testMessageContainer[reference].second += "PASS]";
        
        this->_sendTestResult(
            level, 
            this->_testMessageContainer[reference].first, 
            this->_testMessageContainer[reference].second
        );

        _testMessageContainer.erase(reference);
        _availableMapAddresses.push(reference);
    }
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