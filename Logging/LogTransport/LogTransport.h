#ifndef LOGTRANSPORT_H
#define LOGTRANSPORT_H

#include <chrono>
#include <iostream>
#include "../LogStatus.h"
#include "../LogType.h"

namespace RCU
{

class LogTransport
{
private:
    bool _enabled;
    unsigned int _epoch;
    void _updateTime();

protected:
    unsigned int _getTimeMs();

public:
    LogTransport();
    void enable();
    void disable();
    virtual RCU::LogStatus sendLog(LogType LogType, const char* LogContext) = 0;
};
    
} // namespace RCU

#endif //LOGTRANSPORT_H