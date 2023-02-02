#ifndef CONSOLE_H
#define CONSOLE_H

#include "../../LogStatus.h"
#include "../../LogType.h"
#include "../LogTransport.h"

namespace RCU
{

class Console : public LogTransport
{
public:
    Console();
    RCU::LogStatus sendLog(RCU::LogType level, const char* message, const char* fullMessage) override;
}; 
    
} // namespace RCU


#endif //CONSOLE_H