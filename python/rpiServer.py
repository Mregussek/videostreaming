#!usr/bin/env python
# Written by Mateusz Rzeczyca

from src.network import Network
from src.camera import Camera

server = Network()
camera = Camera()

server.set_address('127.0.0.1', 7123, 'tcp')
server.create_socket()
server.create_server()
server.listen_for_coonnection()
server.accept_first()

while(True):
    image = camera.read_frame()
    decode = camera.decode_image(image)
    server.send_data(decode)

    if image.data < 0:
        break

server.close_connection()