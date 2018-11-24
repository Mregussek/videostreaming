cmake_minimum_required(VERSION 3.6)

project(videoStream)

SET(COMPILE_DEFINITIONS -Werror)

include_directories(SYSTEM ${PIROOT}/opt/vc/include ${PIROOT}/opt/vc/include/interface/vcos/pthreads ${PIROOT}/opt/vc/include/interface/vmcs_host/linux )
link_directories( ${PIROOT}/opt/vc/lib )

# Use OpenCV package
set(OpenCV_DIR "/usr/lib/opencv")
find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/network.cpp src/network.h main.cpp src/camera.cpp src/camera.h)
add_executable(videoStream ${SOURCE_FILES})

target_link_libraries(videoStream ${OpenCV_LIBS})