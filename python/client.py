# Video Streaming with Picamera
# made by Mateusz Rzeczyca
# This file run on your machine

import socket
import cv2
import numpy as np

clientSocket = socket.socket()

# run server
address = ('0.0.0.0', 3305)
connection = clientSocket.connect(address)

columns = 640
rows = 480
resolution = (columns, rows)

cv2.namedWindow('VideoStream')

while 1:
    data, server = connection.recvfrom(65507)

    print("Data length: {}".format(len(data)))
    if len(data) == 4:
        break

    array = np.frombuffer(data, dtype=np.dtype('uint8'))
    image = cv2.imdecode(array, 1)
    cv2.imshow("Image", image)

clientSocket.close()
