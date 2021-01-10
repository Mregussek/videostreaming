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


class UDPClient(object):
    '''
    UDPClient - class for creating connection between server and RPi.

    Correct other for actions is to create_socket, connect_to_server
    and then in loop send encoded images.
    '''

    def __init__(self):
        """
        Creates UDPClient instance with server_socket.
        """

        self.client_socket = None

    def create_socket(self):
        """
        Initializes client_socket. Sets client_socket to be 
        a UDP socket.
        """

        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    def connect_to_server(self, server_addr):
        """
        Connects to server, which should have given ip address and port. 
        Make sure that create_socket() method was called before. 

        Attributes:
            addr(tuple): address and port in tuple, where (ip_addr, port)
        """

        addr = (server_addr[0], int(server_addr[1]))
        self.client_socket.connect(addr)

    def send_data(self, data):
        """
        Sends encoded data to connected server.

        Attributes:
            data(str): encoded data in string format
        """

        self.client_socket.sendall(data)


class Camera(object):
    """
    Camera - class for reading input from camera and encoding
    it to format that can be send by sockets.
    """

    def __init__(self):
        """
        Creates camera instance and sets default values to self.camera
        and self.resolution.
        """

        self.camera = None
        self.resolution = (320, 240)

    def create(self):
        """
        Creates camera object and starting to use it.
        """

        self.camera = cv2.VideoCapture(0)

    def read_frame(self):
        """
        Reads frame from camera. Then checks if camera was able to read
        frame. If was return that frame, if not return None.

        Returns:
            frame(cv2.mat): returns frame in cv2.mat if was possible to retrieve it.
        """

        is_there_frame, frame = self.camera.read()
        if is_there_frame:
            return frame
        else:
            return None

    def resize_frame(self, frame):
        """
        Resizes given frame to self.resolution. Then returns resized image.

        Attributes:
            frame(cv2.mat): frame that will be resized

        Returns:
            resized_frame(cv2.mat): resized frame
        """

        resized_frame = cv2.resize(frame, self.resolution)
        return resized_frame

    def encode_image(self, image):
        """
        Encodes image in base64 format and to .jpg format by openCV.
        Then return encoded image in string format. After this operation
        frame can be send through sockets.

        Attributes:
            image(cv2.mat): image that will be encoded
        
        Returns:
            as_text(str): encoded image in string format
        """

        _, encoded = cv2.imencode('.jpg', image)
        as_text = base64.b64encode(encoded)
        return as_text

    def destroy(self):
        """
        Destroys created camera and all windows.
        """

        self.camera.release()
        cv2.destroyAllWindows()


class ArgParser(object):

    def __init__(self):
        """
        Initializes argument parser and saves all parsed data self.args variable.
        Use self.args.ip to retrieve given IPv4 address and self.args.port to retrieve port number.
        """

        parser = argparse.ArgumentParser()
        parser.add_argument('-i', '--ip', help='Server Ipv4 address', type=str, required=True)
        parser.add_argument('-p', '--port', help='Server Ipv4 port', type=str, required=True)
        self.args = parser.parse_args()

    def get_server_data(self):
        """
        Returns server data in tuple format.

        Returns:
            server_data(tuple): (ip_addr, port)
        """

        return (self.args.ip, self.args.port)


if __name__ == '__main__':
    args = ArgParser()    
    server_addr = args.get_server_data()

    client = UDPClient()
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