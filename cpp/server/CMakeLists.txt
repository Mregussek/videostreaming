# CMake version check
cmake_minimum_required(VERSION 3.6)

# Create project
project(serverRPi)

# Enable c++11 standard
set(CMAKE_CXX_STANDARD 11)

# Add myServer.cpp file to SOURCE FILES
set(SOURCE_FILES myServer.cpp)

# Add executable target with source
add_executable(serverRPi ${SOURCE_FILES})

# Look for OpenCV
find_package(OpenCV REQUIRED)
target_link_libraries(serverRPi ${OpenCV_LIBS})
