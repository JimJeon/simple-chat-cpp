cmake_minimum_required (VERSION 3.8)
project (cpp-chat-linux)

set (CMAKE_EXPORT_COMPILE_COMMANDS "ON")
set (CMAKE_CXX_STANDARD 11)

include_directories (include)
find_package (Threads)

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

file (GLOB CLIENT_SOURCES "src/client/*.cc" "src/sysmsg.cc")
file (GLOB SERVER_SOURCES "src/server/*.cc" "src/sysmsg.cc")

add_executable (chat ${CLIENT_SOURCES})
add_executable (run_server ${SERVER_SOURCES})
target_link_libraries (run_server ${CMAKE_THREAD_LIBS_INIT})
