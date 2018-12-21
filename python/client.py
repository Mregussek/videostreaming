#!usr/bin/env python
# Written by Mateusz Rzeczyca

from src.network import Network
from src.camera import Camera
import numpy as np

client = Network()
binary = b''

print("Setting address")
client.set_address('127.0.0.1', 7123, 'tcp')

print("Creating socket")
client.create_socket()

print("Connecting to server")
client.connect_to_server()

print("Streaming")
print("---------")
how_many_frames = 0

while (True):
    binary = b''

    while(True):
        print("Receving")
        data = client.receive_data()

        end = data.find(b"END!")

        if end != -1:
            binary += data[:end]
            break

        binary += data

    prepare = np.fromstring(binary, dtype=np.dtype("uint8"))

    print("Decoding {}".format(how_many_frames))
    decoded = Camera.decode_image(prepare)
    how_many_frames += 1

    if isinstance(type(None), type(decoded)):
        break

    print("Showing")
    try:
        Camera.show_image(decoded)
    except:
        pass

client.close_connection()
