# Python Version

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