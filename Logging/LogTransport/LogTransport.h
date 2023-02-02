#ifndef LOGTRANSPORT_H
#define LOGTRANSPORT_H

#include <chrono>
#include <iostream>
#include <mutex>
#include "../LogStatus.h"
#include "../LogType.h"

namespace RCU
{

class LogTransport
{
private:
    bool _enabled;
    double _epoch;
    void _updateTime();

protected:
    std::mutex _mutex;
    double _getTimeMs();

public:
    LogTransport();
    void enable();
    void disable();
    virtual RCU::LogStatus sendLog(LogType LogType, std::string_view LogContext, std::string_view fullMessage) = 0;
};
    
} // namespace RCU

#endif //LOGTRANSPORT_H