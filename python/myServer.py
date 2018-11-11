# Video Streaming with Picamera
# made by Mateusz Rzeczyca
# This file run on your machine

import socket
import struct
import io
import cv2
import numpy 

clientSocket = socket.socket()

# run server
address = ('192.168.201.74', 3305)
clientSocket.bind(address)

# listen and accept first connection
clientSocket.listen(0)
connection = clientSocket.accept()[0].makefile('rb')

cv2.namedWindow('VideoStream')

while 1:
    # get length from the image
    # it gets unsigned long 
    imgLength = struct.unpack('<L', connection.read( struct.calcsize('<L') ))[0]

    # when there is no image, quit the loop
    if not imgLength:
        break

    # stream, which will hold data for every frame    
    imgStream = io.BytesIO()
    # and read data from connection
    imgStream.write(connection.read(imgLength))

    # set buffer to the beginning
    imgStream.seek(0)

    imgBytes = numpy.asarray(bytearray(imgStream.read()), dtype=numpy.uint8)

    img = cv2.imdecode(imgBytes, cv2.IMREAD_COLOR)

    cv2.imshow('VideoStream', img)


clientSocket.close()