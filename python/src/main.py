from .network import Network
from .camera import Camera
from .test import user_selects_ip
from .test import user_selects_protocol
import os
import time


def clear_screen():
    os.system('cls' if os.name == 'nt' else 'clear')


class Main(Camera, Network):
    def __init__(self):
        Camera.__init__(self)
        Network.__init__(self)

    def menu(self):
        clear_screen()
        print("1. Start watching")
        print("2. Run Server")
        print("3. Configure")
        print("4. Exit")
        choice = input("> ")

        if choice == '1':
            self.run_client()
        elif choice == '2':
            self.run_server()
        elif choice == '3':
            self.configure()
        elif choice == '4':
            exit(0)
        else:
            self.menu()

    def configure(self):
        clear_screen()
        print("1. Change IP for server")
        print("2. Change IP for client")
        print("3. Change Port number")
        print("4. Change protocol")
        print("5. Back")
        choice = input("> ")

        if choice == '1':
            clear_screen()
            print("Your IP for server is: {}".format(self.IP))

            ip = user_selects_ip()
            print("Changed successfully!")
            self.set_ip(ip)
            time.sleep(1)
            self.configure()

        elif choice == '2':
            clear_screen()
            print("Your IP for client is: {}".format(self.IP))

            ip = input('Choose the right IP address: ')
            print("Changed successfully")
            self.set_ip(ip)
            time.sleep(1)
            self.configure()

        elif choice == '3':
            clear_screen()

            print("You PORT is: {}".format(self.PORT))
            port = input('> ')
            self.set_port(int(port))

            print("Changed successfully!")
            time.sleep(1)
            self.configure()

        elif choice == '4':
            clear_screen()
            print("You PROTOCOL is: {}".format(self.PROTOCOL))

            protocol = user_selects_protocol()
            print("Changed successfully!")
            self.set_protocol(protocol)
            time.sleep(1)
            self.configure()

        elif choice == '5':
            self.menu()

        else:
            self.configure()

    def run_client(self):
        if self.PROTOCOL == 'tcp':
            self.run_tcp_client()
        elif self.PROTOCOL == 'udp':
            self.run_udp_client()
        else:
            print("You must change protocol type!")
            self.configure()

    def run_server(self):
        if self.PROTOCOL == 'tcp':
            self.run_tcp_server()
        elif self.PROTOCOL == 'udp':
            self.run_udp_server()
        else:
            print("You must change protocol type!")
            self.configure()

    def run_tcp_client(self):
        self.define_client_tcp()
        self.connect_tcp()

        while True:
            received = self.receive_normal(2048000)
            converted = Camera.convert_image(received)
            ready_image = self.reshape(converted)
            Camera.show_image(ready_image)

            key = Camera.maybe_end()
            if key == 27:
                self.send_data_tcp(b'end')
                break
            else:
                self.send_data_tcp(b'continue')

        self.close_client_connection()

    def run_tcp_server(self):
        self.define_server_tcp()
        self.start_server_tcp()

        self.set_camera()

        while True:
            self.accept_connection_tcp()
            frame = self.read_frame()
            self.send_data_tcp(frame)
            self.receive_end_tcp(1024)

            key = Camera.maybe_end()
            if key == 27:
                break

        Camera.release_camera()
        self.shutdown_server()

    def run_udp_client(self):
        self.define_client_udp()

        while True:
            received = self.receive_normal(2048000)
            converted = Camera.convert_image(received)
            ready_image = self.reshape(converted)
            Camera.show_image(ready_image)

            key = Camera.maybe_end()
            if key == 27:
                break

        self.close_client_connection()

    def run_udp_server(self):
        self.define_server_udp()
        self.start_server_udp()

        self.set_camera()

        while True:
            frame = self.read_frame()
            self.send_data_udp(frame)
            key = Camera.maybe_end()
            if key == 27:
                break

        self.close_client_connection()
