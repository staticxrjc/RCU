#include "LogTransport.h"

namespace RCU
{

void LogTransport::_updateTime()
{
    auto t = std::chrono::high_resolution_clock::now();
    _epoch = t.time_since_epoch().count();
}

unsigned int LogTransport::_getTimeMs() {
    _updateTime();
    return _epoch;
}

LogTransport::LogTransport() {
    _enabled = true;
}

void LogTransport::enable() { _enabled = true; }
void LogTransport::disable() { _enabled = false; }

} // namespace RCU
