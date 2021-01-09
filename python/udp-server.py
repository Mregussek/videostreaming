'''

Written by Mateusz Rzeczyca.
Student - AGH University of Science and Technology.
info@mateuszrzeczyca.pl
09.01.2021

'''


import cv2
import base64
import socket
import numpy as np
import os
import time
import argparse


class UDPServer(object):

    def __init__(self):
        self.server_socket = None

    def create_socket(self):
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    def start_server(self, server_addr):
        self.server_socket.bind(server_addr)

    def receive_data(self):
        data = self.server_socket.recv(30000)
        return data


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
        parser.add_argument('-p', '--port', help='Server Ipv4 port', type=int, required=True)
        self.args = parser.parse_args()

    def get_server_ipv4(self):
        return (self.args.ip, self.args.port)


if __name__ == "__main__":
    args = ArgParser()    
    server_addr = args.get_server_ipv4()

    server = UDPServer()
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
    