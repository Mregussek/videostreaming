import socket
import cv2
import numpy as np
import sys 
import time

address = ('192.168.43.184', 3305)
clientSocket = socket.socket(socket.AF_INET,
                            socket.SOCK_STREAM)

# start server
clientSocket.bind(address)

# listen for 2 devices
clientSocket.listen(5)

# accept connection
connection, adressRPI = clientSocket.accept()

while True:
    # receive data in bytes
    receivedData = connection.recv(4096)

    array = np.frombuffer(receivedData, 
                            dtype =  np.dtype('uint8'))
    img = cv2.imdecode()

    cv2.imshow('Image', img)

    time.sleep(1)

clientSocket.close()