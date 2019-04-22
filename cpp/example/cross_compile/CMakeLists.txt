cmake_minimum_required(VERSION 3.6)

set(COMPILE_DEFINITIONS -Werror -Wall)
add_definitions("-lstdc++")

set(OpenCV_DIR "/usr/lib/opencv")
find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(hw_cmake helloworld.cpp)

target_link_libraries(hw_cmake ${OpenCV_LIBS})