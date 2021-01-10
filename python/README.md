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

Also you can just use requirements.txt:
```bash
pip3 install -r requirements.txt
```

### Run project

Client versions are created to use on RPi, they contain classes written for sending packets and retrieving images from camera.
Server version are created for personal computers. Those files have implemented servers, which receive data from client and then tries to display
decoded image to the window.

TCP version:

- on personal computer please start server:
```bash
python3 tcp-server.py --ip 0.0.0.0 --port 3305
```
- afterwards please start client, which will connect to server:
```bash
python3 tcp-client.py --ip 127.0.0.1 --port 3305
```

UDP version:

- on personal computer please start server:
```bash
python3 udp-server.py --ip 0.0.0.0 --port 3305
```
- afterwards please start client, which will connect to server:
```bash
python3 udp-client.py --ip 127.0.0.1 --port 3305
```

### Possible bugs
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