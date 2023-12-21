add_library(Logger Logger.cpp)

add_subdirectory(LogTransport)
target_link_libraries(
    Logger 
    Console
    Graylog
    File
    LogTransport
)