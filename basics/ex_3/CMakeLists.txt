cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(DataStructuresApproachUCSD)

set(BIN bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_compile_options("-Wall" "-O0" "-g")

# includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Puts all source files to the SOURCES variable.
file (GLOB SOURCES src/*.cc)

# compiles the files defined by SOURCES to generate the executable.
add_executable(${BIN} ${SOURCES})

add_custom_target(
    "debug"
    DEPENDS ${BIN}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
    COMMAND gdb ${BIN} -tui
    )

