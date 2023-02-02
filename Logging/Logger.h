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
class Logger {
protected:
    std::vector<std::unique_ptr<RCU::LogTransport>> _transport;

private:
    RCU::LogType _currentLogLevel;
    RCU::ThreadpoolManager _threadpool;
    void _sendLogs(RCU::LogType level, const char* message, const char* fullMessage);

public:
    Logger();
    ~Logger();
    void fatal(const char* message, const char* fullMessage = nullptr);
    void error(const char* message, const char* fullMessage = nullptr);
    void warning(const char* message, const char* fullMessage = nullptr);
    void info(const char* message, const char* fullMessage = nullptr);
    void debug(const char* message, const char* fullMessage = nullptr);
};                                 

}

#endif //LOGGER_H