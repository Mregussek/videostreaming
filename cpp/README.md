# C++ Version

In **rpi_app** directory you can find code, which have to be run on RPi. You have prepared **CMakeLists.txt** file for building this app.

## Requirements
- [OpenCV](https://opencv.org/)
- [socket](http://www.linuxhowtos.org/C_C++/socket.htm)
- [CMake](https://cmake.org/)

## Installation

### Dependiences

```bash
sudo apt-get install cmake git
```

For installing OpenCV I recommend this
[guide](https://www.pyimagesearch.com/2018/08/15/how-to-install-opencv-4-on-ubuntu/). Socket should be installed manually by the system.

### App
For this I have prepared ***CMakeLists.txt*** file.

```bash
git clone https://github.com/mregussek/videostreaming.git
cd videostreaming/cpp
mkdir build
cd build
cmake ..
```

You can check how many cores your CPU has by ***nproc*** and then run ***make*** command.

```bash
nproc
Example Output: 8

make -j8
```
After that you should be able to ***video*** file in this directory.

```bash
ls

CMakeCache.txt  cmake_install.cmake  video
CMakeFiles      Makefile             VideoStreaming.cbp
```

Now you are able to run it! Examples:

```bash
./video 3305 tcp
./video 10.42.0.30 udp
```

## Possible bugs:
- Cannot open PiCamera by the 0 index.

  It may happen, because for this project I used OpenCV. Creating camera-like object by cv2.VideoCapture(0) don't recognize PiCamera so, you must enable it manually:
```bash
sudo modprobe bcm2835-v4l2
```

## Author
Mateusz Rzeczyca

Student - AGH University of Science and Technology

info@mateuszrzeczyca.pl

Cracow, Poland

21.01.2019

## License
This project is licensed under the GNU GPL3 License - see the LICENSE.md file for details