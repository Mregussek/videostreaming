"""

Written by Mateusz Rzeczyca.
Student - AGH University of Science and Technology
info@mateuszrzeczyca.pl
04.01.2019

"""

import zmq
import numpy as np
import socket


class Network(object):
    def __init__(self):
        self.PORT_TCP = '3305'
        self.CLIENT_ADDR_TCP = 'localhost'
        self.SERVER_TCP = '*'
        self.SERVER_UDP = '127.0.0.1'
        self.CLIENT_ADDR_UDP = '127.0.0.1'
        self.PORT_UDP = 3305
        self.PROTOCOL = 'tcp'
        self.HOST_TCP = '{}://{}:{}'.format(self.PROTOCOL, self.SERVER_TCP, self.PORT_TCP)
        self.CLIENT_TCP = '{}://{}:{}'.format(self.PROTOCOL, self.CLIENT_ADDR_TCP, self.PORT_TCP)
        self.HOST_UDP = (self.SERVER_UDP, int(self.PORT_TCP))
        self.CLIENT_UDP = (self.CLIENT_ADDR_UDP, int(self.PORT_TCP))
        self.context = None
        self.footage_socket = None
        self.client_socket = None

    def define_tcp_server(self):
        self.context = zmq.Context.instance()
        self.footage_socket = self.context.socket(zmq.SUB)

    def tcp_start_server(self):
        self.footage_socket.bind(self.HOST_TCP)
        self.footage_socket.setsockopt_string(zmq.SUBSCRIBE, np.unicode(''))
        print("SERVER STARTED!")

    def receive_from_rpi(self):
        data = self.footage_socket.recv_string()
        return data

    def define_tcp_client(self):
        self.context = zmq.Context()
        self.client_socket = self.context.socket(zmq.PUB)

    def tcp_connect_to_server(self):
        self.client_socket.connect(self.CLIENT_TCP)
        print("Got Connection!")

    def tcp_send_data(self, data):
        self.client_socket.send(data)

    def define_udp_client(self):
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    def udp_connect_to_server(self):
        self.client_socket.connect(self.CLIENT_UDP)
        print("Got connection!")

    def udp_send_data(self, data):
        self.client_socket.sendall(data)

    def define_udp_server(self):
        self.footage_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    def udp_start_server(self):
        self.footage_socket.bind(self.HOST_UDP)
        print('SERVER STARTED!')

    def udp_receive_data(self):
        data = self.footage_socket.recv(30000)
        return data

    def set_server_ip(self, ip):
        self.SERVER_TCP = ip
        self.SERVER_UDP = ip

        if self.SERVER_TCP == '127.0.0.1':
            self.SERVER_TCP = '*'

        self.HOST_TCP = '{}://{}:{}'.format(self.PROTOCOL, self.SERVER_TCP, self.PORT_TCP)
        self.HOST_UDP = (self.SERVER_UDP, int(self.PORT_TCP))

    def set_client_ip(self):
        while True:
            ip = input("Change it to: ")
            print("Is this IP address correct: {}".format(ip))
            correctness = input('[y/n]')
            if correctness == 'y' or correctness == 'Y':
                self.CLIENT_ADDR_TCP = ip
                self.CLIENT_ADDR_UDP = ip

                if self.CLIENT_ADDR_TCP == '127.0.0.1':
                    self.CLIENT_ADDR_TCP = 'localhost'

                print("Changed successfully!")
                break

        self.CLIENT_TCP = '{}://{}:{}'.format(self.PROTOCOL, self.CLIENT_ADDR_TCP, self.PORT_TCP)
        self.CLIENT_UDP = (self.CLIENT_ADDR_UDP, int(self.PORT_TCP))

    def set_port(self):
        while True:
            port = input("Change it to: ")
            print("Is this PORT number correct: {}".format(port))
            correctness = input('[y/n]')
            if correctness == 'y' or correctness == 'Y':
                self.PORT_TCP = port
                print("Changed successfully!")
                break

        self.HOST_TCP = '{}://{}:{}'.format(self.PROTOCOL, self.SERVER_TCP, self.PORT_TCP)
        self.CLIENT_TCP = '{}://{}:{}'.format(self.PROTOCOL, self.CLIENT_ADDR_TCP, self.PORT_TCP)
        self.HOST_UDP = (self.SERVER_UDP, int(self.PORT_TCP))
        self.CLIENT_UDP = (self.CLIENT_ADDR_UDP, int(self.PORT_TCP))

    def set_protocol(self, protocol):
        self.PROTOCOL = protocol
        self.HOST_TCP = '{}://{}:{}'.format(self.PROTOCOL, self.SERVER_TCP, self.PORT_TCP)
        self.CLIENT_TCP = '{}://{}:{}'.format(self.PROTOCOL, self.CLIENT_ADDR_TCP, self.PORT_TCP)

