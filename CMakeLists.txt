cmake_minimum_required(VERSION 3.18)
project(RCU VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Threadpool)
add_subdirectory(Network)
add_subdirectory(Logging)
add_subdirectory(Parsers)

set(SFML_FILES RCUSFML.cpp RCUSFML.h)

add_library(
    ${PROJECT_NAME} STATIC
    RCU.cpp
    )

    target_link_libraries(${PROJECT_NAME} 
        Logger
        ThreadpoolManager
        Server
        Client
        Socket
        JSONParser
    )

set_source_files_properties(
    ${SFML_FILES}
    PROPERTIES
    COMPILE_OPTIONS "-w"
)
    
if(INCLUDE_SFML)
    add_subdirectory(Managers)
    add_subdirectory(StateMachine)
    add_subdirectory(GameData)
    find_package(SFML 2.5 COMPONENTS network audio graphics window system REQUIRED)
    if(SFML_FOUND)
        add_library(
            ${PROJECT_NAME}_SFML STATIC
            ${SFML_FILES}
        )
        include_directories(${SFML_INCLUDE_DIR})
        # SFML version >= 2.5
        #In SFML Version 2.5 or later, ${SFML_LIBRARIES}, ${SFML_DEPENDENCIES}, ${SFML_INCLUDE_DIR} no longer exist. Specify libraries individually.
        target_link_libraries(
            ${PROJECT_NAME}_SFML 
            GameData
            StateMachine
            Managers
            sfml-network 
            sfml-audio 
            sfml-graphics 
            sfml-window 
            sfml-system)
        target_link_libraries(
            ${PROJECT_NAME}
            ${PROJECT_NAME}_SFML
        )
        
        endif()
endif()

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)