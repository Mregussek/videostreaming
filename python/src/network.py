#!usr/bin/env python
# Made by Mateusz Rzeczyca.

import socket


class Network(object):
    def __init__(self):
        self.portNumber = 7123
        self.ipAddress = '127.0.0.1'
        self.protocolType = 'tcp'
        self.hostAddress = (self.ipAddress, self.portNumber)
        self.sockSystemCall = None
        self.acceptSystemCall = None

    def set_address(self, ip, port, protocol):
        self.portNumber = port
        self.ipAddress = ip
        self.protocolType = protocol
        self.hostAddress = (ip, port)

    def create_server(self):
        self.sockSystemCall.bind(self.hostAddress)

    def create_socket(self):
        if self.protocolType == 'tcp':
            self.sockSystemCall = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        elif self.protocolType == 'udp':
            self.sockSystemCall = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        else:
            exit(0)

    def listen_for_connection(self):
        self.sockSystemCall.listen(5)

    def accept_first(self):
        if self.acceptSystemCall is None:
            self.acceptSystemCall, _ = self.sockSystemCall.accept()

    def close_connection(self):
        self.sockSystemCall.shutdown()
        self.sockSystemCall.close()

    def receive_data(self):
        data = self.sockSystemCall.recv(4096000)

        if len(data) == 0:
            exit(0)

        return data

    def send_data(self, data):
        try:
            self.acceptSystemCall.send(data)
        except:
            pass

    def connect_to_server(self):
        _ = self.sockSystemCall.connect(self.hostAddress)
