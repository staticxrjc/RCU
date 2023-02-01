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
    LogStatus sendLog(LogType level, const char* message) override;
}; 
    
} // namespace RCU


#endif //CONSOLE_H