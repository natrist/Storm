set(EXECUTABLE_NAME StormConsole)

message("Building StormConsole.exe")
include_directories(${PROJECT_SOURCE_DIR}/Storm)
link_directories(${PROJECT_SOURCE_DIR}/Storm)
file(GLOB STORM_CONSOLE_SOURCES ./*.cpp)

add_executable(${EXECUTABLE_NAME} ${STORM_CONSOLE_SOURCES})
target_link_libraries(${EXECUTABLE_NAME} ${LIBRARY_NAME})
