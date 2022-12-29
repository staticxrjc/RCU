cmake_minimum_required(VERSION 3.18)
project(RCU VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Threadpool)
add_subdirectory(Managers)
add_subdirectory(StateMachine)
add_subdirectory(GameData)

add_library(
    ${PROJECT_NAME}
    RCU.cpp
)
target_link_libraries(${PROJECT_NAME}
    ThreadpoolManager
)

find_package(SFML 2.5 COMPONENTS network audio graphics window system REQUIRED)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  # SFML version >= 2.5
  #In SFML Version 2.5 or later, ${SFML_LIBRARIES}, ${SFML_DEPENDENCIES}, ${SFML_INCLUDE_DIR} no longer exist. Specify libraries individually.
  target_link_libraries(
    ${PROJECT_NAME} 
    GameData
    StateMachine
    Managers
    sfml-network 
    sfml-audio 
    sfml-graphics 
    sfml-window 
    sfml-system)
endif()


target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")