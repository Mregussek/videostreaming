# CMake version check
cmake_minimum_required(VERSION 3.6)

# Create project
project(clientRPi)

# Enable c++11 standard
#set(CMAKE_CXX_STANDARD 11)

# Add myClient.cpp file of project root directory as source file
set(SOURCE_FILES myClient.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(clientRPi ${SOURCE_FILES})

# Use Threads package
find_package(Threads REQUIRED)
target_link_libraries(clientRPi ${CMAKE_THREAD_LIBS_INIT})

# Use OpenCV package
find_package(OpenCV REQUIRED)
target_link_libraries(clientRPi ${OpenCV_LIBS})

# for cross compilation

SET(CMAKE_TOOLCHAIN_FILE ~/RPi/opencv/platforms/linux/arm-gnueabi.toolchain.cmake)

# some issues with code below ...
# specify system version
#SET(CMAKE_SYSTEM_NAME Linux)
#SET(CMAKE_SYSTEM_VERSION 1)

# Specify the cross compiler
#SET(CMAKE_C_COMPILER $ENV{HOME}/Development/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc)
#SET(CMAKE_CXX_COMPILER $ENV{HOME}/Development/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-g++)

# Where is the target environment
#SET(CMAKE_FIND_ROOT_PATH $ENV{HOME}/Development/raspberrypi/rootfs)

# Search for programs only in the build host directories
#SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# Search for libraries and headers only in the target directories
#SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
#SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
