#include "LogTransport.h"

namespace RCU
{

void LogTransport::_updateTime()
{
    auto t = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
    _epoch = static_cast<double>(t.count());
}

double LogTransport::_getTimeMs() {
    _updateTime();
    return _epoch/1000;
}

LogTransport::LogTransport() {
    _enabled = true;
}

void LogTransport::enable() { _enabled = true; }
void LogTransport::disable() { _enabled = false; }

} // namespace RCU
