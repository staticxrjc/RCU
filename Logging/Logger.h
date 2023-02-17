#ifndef LOGGER_H
#define LOGGER_H
#include <memory>
#include "LogStatus.h"
#include "LogType.h"
#include "LogTransport/Console/Console.h"
#include "LogTransport/Graylog/Graylog.h"
#include "../Threadpool/ThreadpoolManager.h"
#include <map>
#include <mutex>

namespace RCU {

class LogTransport;

class Logger {
protected:
    std::vector<std::unique_ptr<RCU::LogTransport>> _transport;

private:
    std::mutex _mtx;

    std::mutex _testMtx;
    std::queue<int> _availableMapAddresses;
    std::map<int,std::pair<std::string,std::string>> _testMessageContainer; // used in conjunction with test method

    RCU::LogType _currentLogLevel;
    RCU::ThreadpoolManager _threadpool;
    void _sendLogs(RCU::LogType level, const std::string &message, const std::string &fullMessage);
    void _sendTestResult(RCU::LogType level, const std::string &uncodedMessage, const std::string &codedMessage);

public:
    Logger();
    virtual ~Logger();
    void fatal(const std::string &message, const std::string &fullMessage = "");
    void error(const std::string &message, const std::string &fullMessage = "");
    void warning(const std::string &message, const std::string &fullMessage = "");
    void info(const std::string &message, const std::string &fullMessage = "");
    void debug(const std::string &message, const std::string &fullMessage = "");
    /**
     * @brief Test condition to be used with try/catch blocks, on success use pass, else fail
     * 
     * @param message Condition to be tested
     * @return Reference to be passed into pass/fail
     */
    int test(const std::string &message);
    void pass(RCU::LogType level, int reference);
    void fail(RCU::LogType level, int reference);
    void awaitSendLogs();
};                                 

}

#endif //LOGGER_H