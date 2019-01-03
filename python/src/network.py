import zmq
import numpy as np


class Network(object):
    def __init__(self):
        self.PORT = '3305'
        self.CLIENT_IP = 'localhost'
        self.SERVER_IP = '*'
        self.PROTOCOL = 'udp'
        self.HOST = '{}://{}:{}'.format(self.PROTOCOL, self.SERVER_IP, self.PORT)
        self.CLIENT = '{}://{}:{}'.format(self.PROTOCOL, self.CLIENT_IP, self.PORT)
        self.context = None
        self.footage_socket = None
        self.client_socket = None

    def define_tcp_server(self):
        self.context = zmq.Context.instance()
        self.footage_socket = self.context.socket(zmq.SUB)

    def tcp_start_server(self):
        self.footage_socket.bind(self.HOST)
        self.footage_socket.setsockopt_string(zmq.SUBSCRIBE, np.unicode(''))
        print("SERVER STARTED!")

    def receive_from_rpi(self):
        data = self.footage_socket.recv_string()
        return data

    def define_tcp_client(self):
        self.context = zmq.Context()
        self.client_socket = self.context.socket(zmq.PUB)

    def connect_to_server(self):
        self.client_socket.connect(self.CLIENT)
        print("Got Connection!")

    def tcp_send_data(self, data):
        self.client_socket.send(data)

    def define_udp_server(self):
        self.context = zmq.Context()
        self.footage_socket = self.context.socket(15)

    def udp_server_start(self):
        self.footage_socket.bind(self.HOST)
        print("SERVER STARTED!")

    def define_udp_client(self):
        self.context = zmq.Context()
        self.client_socket = self.context.socket(14)

    def udp_send_data(self, data):
        self.client_socket.send(data)

    def set_server_ip(self, ip):
        self.SERVER_IP = ip
        self.HOST = '{}://{}:{}'.format(self.PROTOCOL, self.SERVER_IP, self.PORT)

    def set_client_ip(self):
        while True:
            ip = input("Change it to: ")
            print("Is this IP address correct: {}".format(ip))
            correctness = input('[y/n]')
            if correctness == 'y' or correctness == 'Y':
                self.CLIENT_IP = ip
                print("Changed successfully!")
                break

        self.CLIENT = '{}://{}:{}'.format(self.PROTOCOL, self.CLIENT_IP, self.PORT)

    def set_port(self):
        while True:
            port = input("Change it to: ")
            print("Is this PORT number correct: {}".format(port))
            correctness = input('[y/n]')
            if correctness == 'y' or correctness == 'Y':
                self.PORT = port
                print("Changed successfully!")
                break

        self.HOST = '{}://{}:{}'.format(self.PROTOCOL, self.SERVER_IP, self.PORT)
        self.CLIENT = '{}://{}:{}'.format(self.PROTOCOL, self.CLIENT_IP, self.PORT)

    def set_protocol(self, protocol):
        self.PROTOCOL = protocol
        self.HOST = '{}://{}:{}'.format(self.PROTOCOL, self.SERVER_IP, self.PORT)
        self.CLIENT = '{}://{}:{}'.format(self.PROTOCOL, self.CLIENT_IP, self.PORT)

