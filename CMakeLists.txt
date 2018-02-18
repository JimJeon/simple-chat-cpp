cmake_minimum_required (VERSION 3.8)
project (cpp-chat-linux)

set (CMAKE_EXPORT_COMPILE_COMMANDS "ON")

include_directories (include)

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

file (GLOB CLIENT_SOURCES "src/client/*.cc")
file (GLOB SERVER_SOURCES "src/server/*.cc")

add_executable (chat ${CLIENT_SOURCES})
add_executable (run_server ${SERVER_SOURCES})
