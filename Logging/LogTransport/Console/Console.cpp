#include "Console.h"

namespace RCU
{

Console::Console() : LogTransport() {}

RCU::LogStatus Console::sendLog(RCU::LogType level, const char *message)
{
    switch(level) {
        case RCU::LogType::FATAL:
            std::cout << "[FATAL][";
            break;
        case RCU::LogType::ERR:
            std::cout << "[ERROR][";
            break;
        case RCU::LogType::WARNING:
            std::cout << "[WARNING][";
            break;
        case RCU::LogType::INFO:
            std::cout << "[INFO][";
            break;
        case RCU::LogType::DEBUG:
            std::cout << "[DEBUG][";
            break;
        default:
            return RCU::LogStatus::FAILED_GENERIC;
    }  
    auto time = _getTimeMs();
    std::cout << time << "]: " << message << std::endl;
    return RCU::LogStatus::SUCCESS;
}

} // namespace RCU
