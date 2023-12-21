#include "File.h"

RCU::File::File(const std::string& file) : LogTransport() {
    mOutputFile.open(file);
    if (!mOutputFile) {
        std::cerr << "Error opening " << file << "\n";
    }
}

RCU::File::~File() {
    if(mOutputFile.is_open())
        mOutputFile.close();
}

RCU::LogStatus RCU::File::sendLog(RCU::LogType level, std::string_view message, std::string_view fullMessage) {
    if(!mOutputFile.is_open()) return RCU::LogStatus::FAILED_FILE;
    std::stringstream fileOut;
        switch(level) {
            case RCU::LogType::FATAL:
                fileOut << "[FATAL][";
                break;
            case RCU::LogType::ERR:
                fileOut << "[ERROR][";
                break;
            case RCU::LogType::WARNING:
                fileOut << "[WARNING][";
                break;
            case RCU::LogType::INFO:
                fileOut << "[INFO][";
                break;
            case RCU::LogType::DEBUG:
                fileOut << "[DEBUG][";
                break;
            default:
                return RCU::LogStatus::FAILED_FILE;
        }
        auto time = _getTimeMs();
        fileOut << std::to_string(time) << "]: " << message << std::endl;
        if(fullMessage != message)
            fileOut << "[FULLMESSAGE]:\n " << fullMessage << std::endl;
    {
        std::unique_lock lock(_mutex);
        mOutputFile << fileOut.str();
    }
    return RCU::LogStatus::SUCCESS;
}

