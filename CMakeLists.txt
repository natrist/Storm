cmake_minimum_required(VERSION 3.9)

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Maps to Visual Studio solution file (Storm.sln)
# The solution will have all targets (exe, lib, dll) 
# as Visual Studio projects (.vcproj)
project (Storm)

add_subdirectory(Source)

option(VAR_CONSOLE_STORM "Generate ConsoleStorm project for tests" ON)

if (VAR_CONSOLE_STORM)
    add_executable(ConsoleStorm Source/ConsoleStorm.cpp)
    target_link_libraries(ConsoleStorm StormLib)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ConsoleStorm)
endif(VAR_CONSOLE_STORM)
