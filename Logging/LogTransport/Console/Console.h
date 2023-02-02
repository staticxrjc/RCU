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
    RCU::LogStatus sendLog(RCU::LogType level, std::string_view message, std::string_view fullMessage) override;
}; 
    
} // namespace RCU


#endif //CONSOLE_H