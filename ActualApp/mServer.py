# Made by Mateusz Rzeczyca
# on the machine, which listens for data from rpi

import socket

# creating an object
mySocket = socket.socket()

# creating a server
address = ("192.168.43.70", 3305)
mySocket.bind(address)

# listen for 2 devices
mySocket.listen(2)

# accept connection
connection, adressRPI = mySocket.accept()

while True:
    # receive data in bytes
    receivedData =connection.recv(1000)

    print(receivedData)

connection.close()
mySocket.close()

