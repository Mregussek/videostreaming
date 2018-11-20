# Get that photo from RPi
# Made by Mateusz Rzeczyca

import socket
import cv2

# creating an object
mySocket = socket.socket()

# creating a server
address = ('10.42.0.30', 3305)
connection = mySocket.connect(address)
helper = ""

while True:
    # receive data in bytes
    receivedData = connection.recv(8 * 1024)

    if receivedData > 0
        helper = receivedData
        break

decodedData = helper.decode()
img = cv2.imdecode(decodedData, 1)
cv2.imshow("Image", img)

connection.close()
mySocket.close()

