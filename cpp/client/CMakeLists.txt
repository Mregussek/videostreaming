cmake_minimum_required(VERSION 3.6)# CMake version check
project(clientRPi)                 # Create project
set(CMAKE_CXX_STANDARD 11)         # Enable c++17 standard

set(SOURCE_FILES myClient.cpp)     # Add myClient.cpp file of project root
                                   #directory as source file
add_executable(clientRPi ${SOURCE_FILES}) # Add executable target with source
                                          #files listed in SOURCE_FILES variable

find_package(Threads)
target_link_libraries(clientRPi ${CMAKE_THREAD_LIBS_INIT})

find_package(OpenCV REQUIRED)
target_link_libraries(clientRPi ${OpenCV_LIBS})
