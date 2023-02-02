add_library(LogTransport
    LogTransport.cpp
)

add_subdirectory(Console)
add_subdirectory(Graylog)

target_link_libraries(
    LogTransport 
    Console
    Graylog
)