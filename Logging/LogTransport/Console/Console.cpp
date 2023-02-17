#include "Console.h"
#include <string>

namespace RCU
{

Console::Console() : LogTransport() { this->_colorSupport = true; }

RCU::LogStatus Console::sendLog(RCU::LogType level, std::string_view message, std::string_view fullMessage)
{
    {
        std::unique_lock lock(_mutex);
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
        std::cout << std::to_string(time) << "]: " << message << std::endl;
        if(fullMessage != message)
            std::cout << "[FULLMESSAGE]:\n " << fullMessage << std::endl;
    }
    return RCU::LogStatus::SUCCESS;
}

} // namespace RCU
