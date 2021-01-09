'''

Written by Mateusz Rzeczyca.
Student - AGH University of Science and Technology.
info@mateuszrzeczyca.pl
09.01.2021

'''


import cv2
import base64
import zmq
import numpy as np
import os
import time
import argparse


class TCPClient(object):

    def __init__(self):
        self.context = None
        self.client_socket = None

    def create_socket(self):
        self.context = zmq.Context.instance()
        self.client_socket = self.context.socket(zmq.PUB)

    def connect_to_server(self, ip_addr):
        self.client_socket.connect(ip_addr)

    def send_data(self, data):
        self.client_socket.send(data)


class Camera(object):
    
    def __init__(self):
        self.camera = None
        self.resolution = (640, 480)

    def create(self):
        self.camera = cv2.VideoCapture(0)

    def read_frame(self):
        is_there_frame, frame = self.camera.read()
        if is_there_frame:
            return frame
        else:
            return None

    def resize_frame(self, frame):
        resized_frame = cv2.resize(frame, self.resolution)
        return resized_frame

    def encode_image(self, image):
        _, encoded = cv2.imencode('.jpg', image)
        as_text = base64.b64encode(encoded)
        return as_text

    def destroy(self):
        self.camera.release()
        cv2.destroyAllWindows()


class ArgParser(object):

    def __init__(self):
        parser = argparse.ArgumentParser()
        parser.add_argument('-i', '--ip', help='Server Ipv4 address', type=str, required=True)
        parser.add_argument('-p', '--port', help='Server Ipv4 port', type=str, required=True)
        self.args = parser.parse_args()

    def get_server_ipv4(self):
        return '{}://{}:{}'.format(
            'tcp', 
            self.args.ip, 
            self.args.port
        )


if __name__ == "__main__":
    args = ArgParser()    
    server_addr = args.get_server_ipv4()

    client = TCPClient()
    camera = Camera()

    client.create_socket()
    client.connect_to_server(server_addr)

    camera.create()

    while True:
        try:
            frame = camera.read_frame()
            if frame is None:
                continue

            resized_frame = camera.resize_frame(frame)
            encoded_frame_as_text = camera.encode_image(frame)

            client.send_data(encoded_frame_as_text)
        except KeyboardInterrupt:
            break

    camera.destroy()
