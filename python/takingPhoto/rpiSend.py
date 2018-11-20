# Send that photo to host
# Made by Mateusz Rzeczyca

import socket

CHUNK_SIZE = 8 * 1024

mySocket = socket.socket()

address = ("10.42.0.30", 3305)

mySocket.bind(address)
mySocket.listen(1)
connection = mySocket.accept()

file = open('rpiPhoto,jpg')
data = file.read(CHUNK_SIZE)
encodedData = data.encode()
mySocket.send(encodedData)

mySocket.close()
