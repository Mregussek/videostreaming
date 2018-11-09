cmake_minimum_required(VERSION 3.6)# CMake version check
project(clientRPi)                 # Create project
set(CMAKE_CXX_STANDARD 11)         # Enable c++11 standard

set(SOURCE_FILES myClient.cpp)     # Add myClient.cpp file of project root
                                   #directory as source file
add_executable(clientRPi ${SOURCE_FILES}) # Add executable target with source
                                            #files listed in SOURCE_FILES variable

find_package(Threads)
target_link_libraries(clientRPi ${CMAKE_THREAD_LIBS_INIT})

find_package(OpenCV REQUIRED)
target_link_libraries(clientRPi ${OpenCV_LIBS})

# specify system version
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_VERSION 1)

# Specify the cross compiler
SET(CMAKE_C_COMPILER $ENV{HOME}/Development/toolchains/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER $ENV{HOME}/Development/toolchains/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-g++)

# Where is the target environment
SET(CMAKE_FIND_ROOT_PATH $ENV{HOME}/Development/toolchains/rootfs)

# Search for programs only in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# Search for libraries and headers only in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
