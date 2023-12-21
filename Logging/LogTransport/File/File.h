#ifndef RCU_FILE_H
#define RCU_FILE_H

#include <fstream>
#include "../../LogStatus.h"
#include "../../LogType.h"
#include "../LogTransport.h"

namespace RCU
{

    class File: public LogTransport
    {
    public:
        explicit File(const std::string& file);
        ~File();
        RCU::LogStatus sendLog(RCU::LogType level, std::string_view message, std::string_view fullMessage) override;
    private:
        std::ofstream mOutputFile;
        std::string mFileName;
    };

} // namespace RCU


#endif // RCU_FILE_H
