# Video Streaming with Picamera
# made by Mateusz Rzeczyca
# This file run on your machine

import socket
import cv2
import struct
import io

clientSocket = socket.socket(socket.AF_INET,
                            socket.SOCK_DGRAM)

# run server
address = ('192.168.137.1', 3305)
clientSocket.bind(address)

# listen and accept first connection
clientSocket.listen(5)
connection = clientSocket.accept()[0].makefile('rb')

cv2.namedWindow('VideoStream')

while 1:
    # get length from the image
    # it gets unsigned long 
    imgLength = struct.unpack('<L', 
        connection.read( struct.calcsize('<L') ))[0]

    # when there is no image, quit the loop
    if not imgLength:
        break

    # stream, which will hold data for every frame    
    imgStream = io.BytesIO()
    # and read data from connection
    imgStream.write( connection.read(imgLength) )

    # set stream to start position
    imgStream.seek(0)

    # decode video from bytes
    img = cv2.imdecode('img.jpg', imgStream)

    # show the image
    cv2.imshow(img)

clientSocket.close()