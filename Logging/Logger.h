#ifndef LOGGER_H
#define LOGGER_H
#include <memory>
#include "LogStatus.h"
#include "LogType.h"
#include "LogTransport/Console/Console.h"
#include "LogTransport/Graylog/Graylog.h"
#include "../Threadpool/ThreadpoolManager.h"

namespace RCU {

class LogTransport;
struct AllocationMetrics
{
    uint32_t totalAllocated = 0;
    uint32_t totalFreed = 0;
    uint32_t currentUsage();
};

class Logger {
protected:
    std::vector<std::unique_ptr<RCU::LogTransport>> _transport;

private:
    RCU::LogType _currentLogLevel;
    RCU::ThreadpoolManager _threadpool;
    void _sendLogs(RCU::LogType level, const std::string &message, const std::string &fullMessage);

public:
    Logger();
    ~Logger();
    void fatal(const std::string &message, const std::string &fullMessage = "");
    void error(const std::string &message, const std::string &fullMessage = "");
    void warning(const std::string &message, const std::string &fullMessage = "");
    void info(const std::string &message, const std::string &fullMessage = "");
    void debug(const std::string &message, const std::string &fullMessage = "");
    static std::string Memory();
};                                 

}

#endif //LOGGER_H