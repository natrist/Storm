# Collect source files into the variable STORM_SOURCES
# without having to explicitly list each header and source file.
file(GLOB STORM_SOURCES "*.cpp" "W32/*.cpp")

list(REMOVE_ITEM STORM_SOURCES "ConsoleStorm.cpp")

if(WIN32)
    file(GLOB STORM_WIN_SOURCES "W32/*.cpp")
endif()
if(APPLE)
        file(GLOB STORM_MAC_SOURCES "Mac/*.cpp")
endif()
if(UNIX AND NOT APPLE)
        file(GLOB STORM_LINUX_SOURCES "Linux/*.cpp")
endif()

# Collect header files into the variable STORM_HEADERS 
file(GLOB STORM_HEADERS "H/*.h" "H/*inl")

# Create VS 'folders' for Source files and Headers
source_group("Source" FILES ${STORM_SOURCES})
source_group("H" FILES ${STORM_HEADERS})

# Create OS specific 'folders' for source files
source_group("Linux" FILES ${STORM_LINUX_SOURCES})
source_group("Mac" FILES ${STORM_MAC_SOURCES})
source_group("W32" FILES ${STORM_WIN_SOURCES})

# Set Properties->General->Configuration Type to Static Library(.lib)
# Creates StormLib.lib with the listed sources collected in the variables
# Also adds source files and headers to the Solution Explorer
add_library(StormLib STATIC ${STORM_SOURCES} ${STORM_HEADERS} ${STORM_LINUX_SOURCES} ${STORM_MAC_SOURCES} ${STORM_WIN_SOURCES})

# Properties->General->Output Directory
set_target_properties(StormLib PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}../bin)
