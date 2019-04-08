cmake_minimum_required(VERSION 3.6)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_C_COMPILER arm-linux-gnueabi-gcc)
set(CMAKE_CXX_COMPILER arm-linux-gnueabi-g++)
set(CMAKE_ASM_COMPILER arm-linux-gnueabi-gcc)
set(CMAKE_SYSTEM_PROCESSOR arm)

add_definitions("-march=armv6")

set(COMPILE_DEFINITIONS -Werror -Wall)

add_executable(hw_cmake helloworld.cpp)