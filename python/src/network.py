#!usr/bin/env python
# Made by Mateusz Rzeczyca.

import socket


class Network(object):
    def __init__(self):
        self.portNumber = 3305
        self.ipAddress = '127.0.0.1'
        self.protocolType = 'tcp'
        self.sockSystemCall = 0
        self.acceptSystemCall = 0
        self.connectSystemCall = 0

    def set_address(self, ip, port, protocol):
        self.portNumber = port
        self.ipAddress = ip
        self.protocolType = protocol
        self.sockSystemCall.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    def create_server(self):
        self.sockSystemCall.bind(self.ipAddress, self.portNumber)

    def create_socket(self):
        if self.protocolType == 'tcp':
            self.sockSystemCall = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        elif self.protocolType == 'udp':
            self.sockSystemCall = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        else:
            exit(0)

    def listen_for_coonnection(self):
        self.sockSystemCall.listen(5)

    def accept_first(self):
        self.acceptSystemCall = self.sockSystemCall.accept()

    def close_connection(self):
        self.sockSystemCall.close()

    def receive_data(self):
        data = self.connectSystemCall.recv(1024)
        return data

    def send_data(self, data):
        self.acceptSystemCall.send(data)

    def connect_to_server(self):
        self.connectSystemCall = self.sockSystemCall.connect(self.ipAddress, self.portNumber)