cmake_minimum_required(VERSION 3.6)

project(videoStream)

set(COMPILE_DEFINITIONS -Werror)

if (CMAKE_CXX_COMPILER_ID STREQUAL GNU)
    set(CXX_FILESYSTEM_LIBRARIES stdc++fs)
else()
    set(CXX_FILESYSTEM_LIBRARIES)
endif()

# Use OpenCV package
set(OpenCV_DIR "/usr/lib/opencv")
find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/network.cpp src/network.h operation.cpp src/camera.cpp src/camera.h src/file.cpp src/file.h src/operation.h src/operation.cpp)
add_executable(videoStream ${SOURCE_FILES})

target_link_libraries(videoStream ${CXX_FILESYSTEM_LIBRARIES})
target_link_libraries(videoStream ${OpenCV_LIBS})
