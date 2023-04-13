cmake_minimum_required(VERSION 3.24)
project(sakora)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pedantic -Wimplicit-fallthrough -Wsequence-point -Wswitch-unreachable -Wstringop-truncation -Wbool-compare -Wtautological-compare -Wfloat-equal -Wshadow=global -Wpointer-arith -Wpointer-compare -Wcast-align -Wcast-qual -Wwrite-strings -Wdangling-else -Wlogical-op -Wconversion -Werror")

file(GLOB SRC_FILES
        "main.cpp",
        "sakConsole/*.h", "sakConsole/*.cpp",
        "error/*.h", "error/*.cpp",
        "Frontend/lexer/*.h", "Frontend/lexer/*.cpp",
        "Frontend/parser/*.h", "Frontend/parser/*.cpp",
        "Backend/visitor/*.h", "Backend/visitor/*.cpp",
        "Backend/type/*.h", "Backend/type/*.cpp",
        "Backend/scope/*.h", "Backend/scope/*.cpp",
        "Backend/object/*.h", "Backend/object/*.cpp",
        "Backend/env/*.h", "Backend/env/*.cpp",
        "Backend/sakCalc/*.h", "Backend/sakCalc/*.cpp",
        "Runner/*.h", "Runner/*.cpp"
        )

        
add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES} )