# Video Streaming with Picamera
# made by Mateusz Rzeczyca
# this file run on RPi

from picamera import PiCamera
from time import sleep
import socket

serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
address = ("10.42.0.30", 7123)

serverSocket.bind(address)
serverSocket.listen(0)
serverSocket.accept()
connection = serverSocket.makefile('wb')

columns = 640
rows = 480
resolution = (columns, rows)

camera = PiCamera()
camera.resolution = resolution
camera.framerate = 10

camera.start_preview()
sleep(2)

camera.start_recording(connection, format='h264')
camera.wait_recording(20)
camera.stop_recording()

connection.close()
serverSocket.close()


