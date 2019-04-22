#   Written by Mateusz Rzeczyca.
#   Student - AGH University of Science and Technology
#   info@mateuszrzeczyca.pl
#   20.01.2019

cmake_minimum_required(VERSION 3.6)

project(VideoStreaming)

set(COMPILE_DEFINITIONS -Werror -Wall)

# Use OpenCV package
set(OpenCV_DIR "/usr/lib/opencv")
find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)


add_executable(video ${SOURCE_FILES} src/networking/client/TCPClient.cpp src/networking/client/TCPClient.h)

target_link_libraries(video ${OpenCV_LIBS})