# RPi Camera stream
## Getting Started
This is video streaming app written for Raspberry Pi.

Of course you can use this app to work with another WebCam, other than RPi.

Package for getting frames is OpenCV so it should work correctly only when you have it installed.

## Observations
Since I used only Python for streaming data, I have seen that this app sometimes losses data. To check this I have written scripts in bash and tested it. It ran correctly. Also I saw that my charger has low voltage to make RPi run properly. We could see an icon about low voltage. Now I am using another one and everything is fine.

## Prepare RPi
I used Raspbian Jessie Lite for to test this app. In the RPiConfiguration directory you have the files, which must be put on your RPi. ***ssh*** file enables connection through 22 port and ***wpa_supplicant.conf*** allows you to connect RPi to WiFi. 

## C++
For TCP I have used 640x480 resolution. It can work without any problems. 

In **rpi_app** directory you can find code, which have to be run on RPi. You have prepared **CMakeLists.txt** file for building this app and **toolchain.cmake** for cross compiling with cmake.

### Cross Compiling
You have to download toolchain for ARM-like processors.

[Toolchain](https://github.com/raspberrypi/tools)
```bash
git clone https://github.com/raspberrypi/tools.git
```
And of course you must have root files and libraries from your RPi in case of correct compiling. If you don't use them, you will see some errors for sure. **toolchain.cmake** is prepared for RPi files in
```
~/rpi/rootfs
```
 directory in your main machine and for toolchain in 
```
~/rpi/tools
```
 directory.

You can get every library installed on your RPi using rsync:
```
rsync -rl --delete-after --safe-links pi@<ip_address>:/{bin,etc,lib,usr} ~/rpi/rootfs
```

### Requirements
- [cv2](https://opencv.org/)
- [socket](http://www.linuxhowtos.org/C_C++/socket.htm)

### Possible bugs:
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