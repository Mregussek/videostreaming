"""

Written by Mateusz Rzeczyca.
Student - AGH University of Science and Technology
info@mateuszrzeczyca.pl
04.01.2019

"""

import socket
import cv2

CHUNK_SIZE = 8 * 1024
null = '0'
nullEncoded = null.encode()

# creating an object
mySocket = socket.socket()

# creating a server
address = ('10.42.0.30', 3305)
connection = mySocket.connect(address)
helper = ""

while True:
    # receive data in bytes
    receivedData = mySocket.recv(CHUNK_SIZE)

    if receivedData > nullEncoded:
        helper = receivedData
        break

decodedData = helper.decode()
img = cv2.imdecode(decodedData, 1)
cv2.imshow("Image", img)

connection.close()
mySocket.close()

