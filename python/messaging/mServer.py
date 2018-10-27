# Made by Mateusz Rzeczyca
# on the machine, which listens for data from rpi

import socket
import time

# creating an object
mySocket = socket.socket()

# creating a server
address = ('192.168.43.184', 3305)
mySocket.bind(address)

print("Server Started")

# listen for 2 devices
mySocket.listen(5)

# accept connection
connection, adressRPI = mySocket.accept()
print("Got connection from {}".format(adressRPI))

while True:
    # receive data in bytes
    receivedData = connection.recv(1024)

    print(receivedData)

    time.sleep(2)

    if receivedData == b'q':
        break


connection.close()
mySocket.close()

