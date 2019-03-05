# RPi Camera stream
## Getting Started
This is video streaming app written for Raspberry Pi.

Of course you can use this app to work with another WebCam, other than RPi.

Package for getting frames is OpenCV so it should work correctly only when you have it installed.

## Observations
Since I used only Python for streaming data, I have seen that this app sometimes losses data. To check this I have written scripts in bash and tested it. It ran correctly. Also I saw that my charger has low voltage to make RPi run properly. We could see an icon about low voltage. Now I am using another one and everything is fine.

## Prepare RPi
I used Raspbian Jessie Lite for to test this app. In the RPiConfiguration directory you have the files, which must be put on your RPi. ***ssh*** file enables connection through 22 port and ***wpa_supplicant.conf*** allows you to connect RPi to WiFi. 

## Python
For TCP in Python I have used 640x480 resolution. It can work without any problems.
On the other hand UDP is set to 320x240 in order to send data properly.

### Requirements
- [cv2](https://pypi.org/project/opencv-python/)
- [base64](https://docs.python.org/3.7/library/base64.html)
- [numpy](http://www.numpy.org/)
- [zmq](http://zeromq.org/)
- [socket](https://docs.python.org/3/library/socket.html)
- [netifaces](https://pypi.org/project/netifaces/)
   
### Install prerequisites
Of course firstly you need to install Python and pip for installing packages. Then:
```bash
pip install opencv-python
pip install numpy
pip install pyzmq
pip install netifaces
```
I presume that [base64](https://docs.python.org/3.7/library/base64.html) and [socket](https://docs.python.org/3/library/socket.html) are already installed by Python.

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

04.01.2019

## License
This project is licensed under the GNU GPL3 License - see the LICENSE.md file for details