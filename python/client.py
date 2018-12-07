#!usr/bin/env python
# Written by Mateusz Rzeczyca

from src.network import Network
from src.camera import Camera

client = Network()
stream = Camera()

client.set_address('127.0.0.1', 7123, 'tcp')
client.create_socket()
client.connect_to_server()

while (True):
    data = client.receive_data()
    encoded = stream.decode_image(data)
    stream.show_image(encoded)

    if encoded.data < 0:
        break

client.close_connection()