#include "File.h"

RCU::File::File(const std::string& file) : LogTransport() {
    mFileName = file;
}

RCU::File::~File() {
}

RCU::LogStatus RCU::File::sendLog(RCU::LogType level, std::string_view message, std::string_view fullMessage) {
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
        mOutputFile.open(mFileName, std::ios::app);
        if(!mOutputFile.is_open()) return RCU::LogStatus::FAILED_FILE;

        mOutputFile << fileOut.str();

        if(mOutputFile.is_open())
            mOutputFile.close();
    }
    return RCU::LogStatus::SUCCESS;
}

