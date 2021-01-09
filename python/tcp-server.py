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


class TCPServer(object):

    def __init__(self):
        self.context = None
        self.server_socket = None

    def create_socket(self):
        self.context = zmq.Context.instance()
        self.server_socket = self.context.socket(zmq.SUB)

    def start_server(self, addr):
        self.server_socket.bind(addr)
        self.server_socket.setsockopt_string(zmq.SUBSCRIBE, np.unicode(''))

    def receive_data(self):
        encoded_as_text = self.server_socket.recv_string()
        return encoded_as_text


class Window(object):

    @staticmethod
    def decode_image(data):
        decoded_b64 = base64.b64decode(data)
        from_string = np.fromstring(decoded_b64, dtype=np.uint8)
        decoded_cv2 = cv2.imdecode(from_string, 1)
        return decoded_cv2
    
    @staticmethod
    def show_image(image):
        cv2.imshow('RPi - Video Transmission', image)
        cv2.waitKey(1)

    @staticmethod
    def destroy():
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

    server = TCPServer()
    server.create_socket()
    server.start_server(server_addr)

    while True:
        try:
            frame = server.receive_data()
            read_to_show_frame = Window.decode_image(frame)
            Window.show_image(read_to_show_frame)

        except KeyboardInterrupt:
            break

    Window.destroy()
    