#!usr/bin/env python
# Written by Mateusz Rzeczyca

from src.network import Network
from src.camera import Camera
import numpy as np

client = Network()
camera = Camera()

print("Setting address")
client.set_address('127.0.0.1', 7143, 'tcp')

print("Creating socket")
client.create_socket()

print("Connecting to server")
client.connect_to_server()

print("Streaming")
print("---------")
how_many_frames = 0

while (True):
    print("Receving")
    data = client.receive_data()

    prepare = np.fromstring(data, dtype=np.uint8)
    try:
        decoded = np.reshape(prepare, camera.resolution)
    except Exception:
        decoded = np.zeros(camera.resolution)

    print("Decoding {}".format(how_many_frames))
    how_many_frames += 1

    print("Showing")
    try:
        Camera.show_image(decoded)
    except:
        pass

client.close_connection()
