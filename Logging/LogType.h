#ifndef LOGTYPE_H
#define LOGTYPE_H

namespace RCU
{

enum class LogType {
    FATAL,
    ERR,
    WARNING,
    INFO,
    DEBUG
};

enum class Transports {
    CONSOLE = 0b00000001,
    GRAYLOG = 0b00000010,
    FILE = 0b00000100,
    OTHER = 0b00001000
};

inline constexpr int 
operator&(int x, Transports y) {
    return x & static_cast<int>(y);
}

inline constexpr int 
operator&(Transports x, Transports y) {
    return static_cast<int>(x) & static_cast<int>(y);
}

inline constexpr int
operator|(Transports x, Transports y) {
    return static_cast<int>(x) | static_cast<int>(y);
}
    
} // namespace RCU
#endif // LOGTYPE_H