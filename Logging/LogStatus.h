#ifndef LOGSTATUS_H
#define LOGSTATUS_H

namespace RCU
{

enum class LogStatus {
    SUCCESS,
    FAILED_NETWORK,
    FAILED_FILE,
    FAILED_GENERIC,
    DISABLED,
    ENABLED
};
    
} // namespace RCU

#endif //LOGSTATUS_H