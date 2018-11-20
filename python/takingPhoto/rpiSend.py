# Send that photo to host
# Made by Mateusz Rzeczyca

import socket
import cv2

CHUNK_SIZE = 8 * 1024

mySocket = socket.socket()

address = ("10.42.0.30", 3305)

mySocket.bind(address)
mySocket.listen(1)
connection = mySocket.accept()

file = cv2.imread('rpiPhoto.jpg', 0)
encodedData = cv2.imencode('jpg', file)
mySocket.send(encodedData)

mySocket.close()
