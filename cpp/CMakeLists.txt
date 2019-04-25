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

# set networking files
set(NET_PATH src/networking)
set(CLIENT_PATH ${NET_PATH}/client)
set(SERVER_PATH ${NET_PATH}/server)

set(CLIENT_FILES ${CLIENT_PATH}/TCPClient.h ${CLIENT_PATH}/TCPClient.cpp ${CLIENT_PATH}/UDPClient.cpp
        ${CLIENT_PATH}/UDPClient.h ${CLIENT_PATH}/client.h)

set(SERVER_FILES ${SERVER_PATH}/TCPServer.h ${SERVER_PATH}/TCPServer.cpp ${SERVER_PATH}/UDPServer.cpp
        ${SERVER_PATH}/UDPServer.h ${SERVER_PATH}/server.h)

set(NET_FILES ${CLIENT_FILES} ${SERVER_FILES})

# set video files
set(VID_PATH src/videoprocessing)
set(VID_FILES ${VID_PATH}/Displayer.h ${VID_PATH}/Displayer.cpp
        ${VID_PATH}/Camera.h ${VID_PATH}/Camera.cpp)

# set main files
set(MAIN_FILES src/Facade.h src/Facade.cpp main.cpp)

# all together
set(SOURCE_FILES ${NET_FILES} ${VID_FILES} ${MAIN_FILES})

add_executable(video ${SOURCE_FILES})

target_link_libraries(video ${OpenCV_LIBS})