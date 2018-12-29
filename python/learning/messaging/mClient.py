# Made by Mateusz Rzeczyca
# on rpi

import socket

# creating an object
mySocket = socket.socket()

# connecting to machine
address = ("127.0.0.1", 3305)
connection = mySocket.connect(address)

while True:
    # get data
    #data = input("> ")

    #dataB = data.encode()

    #mySocket.sendall(dataB)
    receivedData = mySocket.recv(65000)
    print(receivedData)
    #if data == 'q':
        #break

mySocket.close()
