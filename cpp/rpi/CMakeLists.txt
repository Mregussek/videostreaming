cmake_minimum_required(VERSION 3.6)

project(videoStream)

set(COMPILE_DEFINITIONS -Werror -Wall)

# Use OpenCV package
set(OpenCV_DIR "/usr/lib/opencv")
find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_SERVER server.cpp src/Network.cpp src/Network.h src/Camera.cpp src/Camera.h src/Menu.cpp src/Menu.h)
add_executable(server ${SOURCE_SERVER})
target_link_libraries(server ${OpenCV_LIBS})
