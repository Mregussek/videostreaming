import socket


class Network(object):
    def __init__(self):
        self.IP = ''
        self.PORT = 3305
        self.HOST = (self.IP, self.PORT)
        self.PROTOCOL = 'tcp'
        self.server_socket = None
        self.client_socket = None

    def set_ip(self, ip):
        self.IP = ip
        self.HOST = (self.IP, self.PORT)

    def set_port(self, port):
        self.PORT = port
        self.HOST = (self.IP, self.PORT)

    def set_address(self, ip, port):
        self.set_ip(ip)
        self.set_port(port)

    def set_protocol(self, protocol):
        self.PROTOCOL = protocol

    def define_server_tcp(self):
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def define_client_tcp(self):
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def start_server_tcp(self):
        self.server_socket.bind(self.HOST)
        self.server_socket.listen(1)

    def accept_connection_tcp(self):
        if self.client_socket is None:
            self.client_socket, _ = self.server_socket.accept()

    def connect_tcp(self):
        self.client_socket.connect(self.HOST)

    def send_data_tcp(self, data):
        try:
            self.client_socket.send(data)
        except Exception:
            pass

    def receive_normal(self, amount):
        data = self.client_socket.recv(amount)
        return data

    def receive_end_tcp(self, amount):
        try:
            data = self.client_socket.recv(amount)
            if data == 'end':
                self.close_client_connection()
        except Exception:
            self.close_client_connection()

    def shutdown_server(self):
        self.server_socket.close()

    def close_client_connection(self):
        self.client_socket.close()
        self.client_socket = None

    def define_server_udp(self):
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    def define_client_udp(self):
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    def start_server_udp(self):
        self.server_socket.bind(self.HOST)

    def send_data_udp(self, data):
        try:
            self.server_socket.sendall(data)
        except Exception:
            pass
