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
    '''
    UDPServer - class for managing client connections.

    Correct other for actions is to create_socket, start server
    and then in loop receive incoming data.
    '''

    def __init__(self):
        """
        Creates UDPServer instance with server_socket.
        """

        self.server_socket = None

    def create_socket(self):
        """
        Initializes context and server_socket. Sets server_socket to be 
        a UDP socket.
        """

        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    def start_server(self, server_addr):
        """
        Starts server on given ip address and port on server_socket variable. 
        Make sure that create_socket() method was called before. 

        Attributes:
            addr(tuple): address and port in tuple, where (ip_addr, port)
        """

        addr = (server_addr[0], int(server_addr[1]))
        self.server_socket.bind(addr)

    def receive_data(self):
        """
        Receives data from clients and returns them in string format.

        Returns:
            encoded_as_text(str): received data in string format
        """
        
        data = self.server_socket.recv(90000)
        return data


class Window(object):

    @staticmethod
    def decode_image(data):
        """
        Decodes image from base64 format to openCV supported format.

        Attributes:
            data(str): frame encoded by client in base64 format and encoded by openCV

        Returns:
            decoded_cv2(cv2.mat): frame decoded and ready to be shown
        """

        decoded_b64 = base64.b64decode(data)
        from_string = np.frombuffer(decoded_b64, dtype=np.uint8)
        decoded_cv2 = cv2.imdecode(from_string, 1)
        return decoded_cv2
    
    @staticmethod
    def show_image(image):
        """
        Shows given image on window.

        Attributes:
            image(cv2.mat): openCV mat, which will be displayed
        """

        cv2.imshow('RPi - Video Transmission', image)
        cv2.waitKey(1)

    @staticmethod
    def destroy():
        """
        Destroy current openCV windows.
        """

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


if __name__ == "__main__":
    args = ArgParser()    
    server_addr = args.get_server_data()

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
    