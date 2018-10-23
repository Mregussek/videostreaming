# Made by Mateusz Rzeczyca
# on the machine, which listens for data from rpi

import socket

# creating an object
mySocket = socket.socket()

# creating a server
address = ('0.0.0.0', 3305)
mySocket.bind(address)

print("Server Started")

# listen for 2 devices
mySocket.listen(5)

# accept connection
connection, adressRPI = mySocket.accept()
print("Got connection from %s" % str(addr))

while True:
    # receive data in bytes
    receivedData = connection.recv(1024)

    print(receivedData)

connection.close()
mySocket.close()

