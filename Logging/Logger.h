#ifndef LOGGER_H
#define LOGGER_H
#include <memory>
#include "LogStatus.h"
#include "LogType.h"
#include "LogTransport/Console/Console.h"
#include "../Threadpool/ThreadpoolManager.h"

namespace RCU {

class LogTransport;
class Logger {
private:
    std::vector<std::unique_ptr<RCU::LogTransport>> _transport;
    RCU::LogType _currentLogLevel;
    RCU::ThreadpoolManager _threadpool;
    void _sendLogs(RCU::LogType level, const char* message);

public:
    Logger();
    void fatal(const char* message);
    void error(const char* message);
    void warning(const char* message);
    void info(const char* message);
    void debug(const char* message);
    void addLogger(int flags);
    void addLogger(RCU::Transports flag);
};

}

#endif //LOGGER_H