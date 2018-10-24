# Made by Mateusz Rzeczyca
# on rpi

import socket

# creating an object 
mySocket = socket.socket()

# connecting to machine
address = ("192.168.43.184", 3305)
mySocket.connect(address)

while True:
    # get data
    data = input("> ")
    
    dataB = data.encode()

    mySocket.sendall(dataB)

    if data == 'q':
        break

mySocket.close()
