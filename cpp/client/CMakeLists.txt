cmake_minimum_required(VERSION 3.6)

project(videoStream)

set(COMPILE_DEFINITIONS -Werror -Wall)

# Use OpenCV package
set(OpenCV_DIR "/usr/lib/opencv")
find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_SERVER client.cpp src/network.cpp src/network.h src/displayer.cpp src/displayer.h)
add_executable(client ${SOURCE_SERVER})
target_link_libraries(client ${OpenCV_LIBS})