cmake_minimum_required(VERSION 3.18)
project(RCU VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} test.cpp)
add_subdirectory(Threadpool)


target_link_libraries(${PROJECT_NAME} PUBLIC
    threadpoolManager
)