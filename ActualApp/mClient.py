# Made by Mateusz Rzeczyca
# on rpi

import socket

# creating an object 
mySocket = socket.socket()

# connecting to machine
address = ("192.168.43.70", 3305)
mySocket.connect(address)

while True:
    # get data
    data = input("> ")
    
    mySocket.sendall(data)

mySocket.close()
