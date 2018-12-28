#!usr/bin/env python
# Written by Mateusz Rzeczyca

from src.network import Network
from src.camera import Camera

server = Network()
camera = Camera()
camera.set_camera()

print("Setting Address")
server.set_address('', 7143, 'tcp')

print("Creating socket")
server.create_socket()

print("Creating server")
server.create_server()

print("Listening for connections")
server.listen_for_connection()

print("Streaming")
print("-------")
how_many_frames = 0

while(True):
    print("Accepting")
    server.accept_first()

    print("Reading frame {}".format(how_many_frames))
    image = camera.read_frame()
    how_many_frames += 1

    print("Encodind")
    encoded = image.tostring()

    print("Sending")
    server.send_data(encoded)

server.close_connection()
camera.close_camera()
