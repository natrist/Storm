cmake_minimum_required(VERSION 3.8)
project(Storm)

set(LIBRARY_NAME Storm)
set(CMAKE_CXX_STANDARD 11)
option(WITH_STORM_CONSOLE "Compiles StormConsole.exe for library testing." ON)

file(GLOB STORM_SOURCES Storm/*.cpp)
add_library(${LIBRARY_NAME} STATIC ${STORM_SOURCES})

if(WITH_STORM_CONSOLE)
    add_subdirectory(StormConsole)
endif()
