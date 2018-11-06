cmake_minimum_required(VERSION 3.6)# CMake version check
project(serverRPi)                 # Create project
set(CMAKE_CXX_STANDARD 11)         # Enable c++17 standard

set(SOURCE_FILES myServer.cpp)     # Add myClient.cpp file of project root
#directory as source file
add_executable(serverRPi ${SOURCE_FILES}) # Add executable target with source
#files listed in SOURCE_FILES variable

find_package(Threads)
target_link_libraries(serverRPi ${CMAKE_THREAD_LIBS_INIT})

find_package(OpenCV REQUIRED)
target_link_libraries(serverRPi ${OpenCV_LIBS})
