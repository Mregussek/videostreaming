#!usr/bin/env python
# Written by Mateusz Rzeczyca

from src.network import Network
from src.camera import Camera

server = Network()
camera = Camera()

print("Setting Address")
server.set_address('127.0.0.1', 7123, 'tcp')

print("Creating socket")
server.create_socket()

print("Creating server")
server.create_server()

print("Listening for connections")
server.listen_for_connection()

print("Accepting")
server.accept_first()

print("Streaming")
print("-------")
how_many_frames = 0

while(True):
    print("Reading frame {}".format(how_many_frames))
    image = camera.read_frame()
    how_many_frames += 1

    print("Encodind")
    encoded = camera.encode_image(image)

    if encoded == b'':
        break

    print("Sending")
    server.send_data(encoded)

server.close_connection()
