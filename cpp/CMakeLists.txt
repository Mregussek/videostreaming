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

set(MAIN_FILES main.cpp src/main.h src/inc_def.h)

set(NET_DIR src/networking)
set(NET_FILES ${NET_DIR}/TCP.h ${NET_DIR}/TCPclient.h ${NET_DIR}/TCPclient.cpp
        ${NET_DIR}/TCPserver.cpp ${NET_DIR}/TCPserver.h)

set(VID_DIR src/videoprocessing)
set(VID_FILES ${VID_DIR}/VIDEO.h src/videoprocessing/VIDEOclient.cpp src/videoprocessing/VIDEOclient.h src/videoprocessing/VIDEOserver.cpp src/videoprocessing/VIDEOserver.h)

set(SOURCE_FILES ${MAIN_FILES} ${NET_FILES} ${VID_FILES})

add_executable(video ${SOURCE_FILES})

target_link_libraries(video ${OpenCV_LIBS})