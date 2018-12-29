#import socket
#import cv2
#import numpy as np

from src.network import Network
from src.camera import Camera

camera = Camera()
client = Network()
client.set_ip('127.0.0.1')
#IP = ''
#PORT = 3305
#ADDRESS = (IP, PORT)
#HEIGHT = 480
#WIDTH = 640
#CHANNELS = 3
#RESOLUTION = (HEIGHT, WIDTH, CHANNELS)

client.define_tcp()
client.connect()
#client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#client_socket.connect(ADDRESS)

while True:
    received = client.receive_normal(4096000)
    #data = client_socket.recv(4096000)
    converted = Camera.convert_image(received)
    #converted = np.fromstring(data, dtype=np.uint8)

    ready_image = camera.reshape(converted)
    #try:
    #    image = np.reshape(converted, RESOLUTION)
    #except Exception:
    #    image = np.zeros(RESOLUTION)

    Camera.show_image(ready_image)
    #cv2.imshow("ItWorks", image)

    key = Camera.maybe_end()

    if key == 27:
        client.send_data(b'end')
        break
    else:
        client.send_data(b'continue')


