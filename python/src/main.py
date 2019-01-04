"""

Written by Mateusz Rzeczyca.
Student - AGH University of Science and Technology
info@mateuszrzeczyca.pl
04.01.2019

"""

from .network import Network
from .camera import Camera
from .test import user_selects_ip
from .test import user_selects_protocol
import os
import time


def clear_screen():
    os.system('cls' if os.name == 'nt' else 'clear')


def print_usage():
    tcp = """ 
TCP Instruction:
1. Make sure that TCP protocol is set on server and client.
2. Check IP address and port on client and RPi (must be the same).
3. Run first option in the menu (1. Start watching on client)
    on client machine.
4. Run second option (2. RPi start streaming) on RPi
TCP should work properly.
"""

    udp = """
UDP Instruction:
1. Make sure that UDP protocol is set on server and client.
2. Check IP address and port on client and RPi (must be the same).
3. Run second option (2. RPi start streaming) on RPi
4. Run first option in the menu (1. Start watching on client)
    on client machine.
UDP should work properly.
"""
    print(tcp)
    print(60*"-")
    print(udp)


class Main(Camera, Network):
    def __init__(self):
        Camera.__init__(self)
        Network.__init__(self)

    def menu(self):
        clear_screen()
        print(5*"-"+" Current settings "+5*"-")
        print("Server: {} {} {}".format(self.SERVER_UDP, self.PORT_TCP, self.PROTOCOL))
        print("Client: {} {} {}".format(self.CLIENT_ADDR_UDP, self.PORT_TCP, self.PROTOCOL))
        print("-"*28)
        print("1. Start watching on client")
        print("2. RPi start streaming")
        print("3. Configure")
        print("4. Usage")
        print("5. Exit")
        choice = input("> ")

        if choice == '1':
            self.run_client()
        elif choice == '2':
            self.run_server()
        elif choice == '3':
            self.configure()
        elif choice == '4':
            self.usage()
        elif choice == '5':
            exit(0)
        else:
            self.menu()

    def configure(self):
        clear_screen()
        print("1. Change IP for server ({})".format(self.SERVER_UDP))
        print("2. Change IP for client ({})".format(self.CLIENT_UDP))
        print("3. Change Port number ({})".format(self.PORT_TCP))
        print("4. Change protocol ({})".format(self.PROTOCOL))
        print("5. Back")
        choice = input("> ")

        if choice == '1':
            clear_screen()
            print("Your IP for server is: {}".format(self.SERVER_UDP))

            ip = user_selects_ip()
            print("Changed successfully!")
            self.set_server_ip(ip)
            time.sleep(1)
            self.configure()

        elif choice == '2':
            clear_screen()
            print("Your IP for client is: {}".format(self.CLIENT_UDP))

            self.set_client_ip()
            time.sleep(1)
            self.configure()

        elif choice == '3':
            clear_screen()

            print("You PORT number is: {}".format(self.PORT_TCP))
            self.set_port()

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
    
    def usage(self):
        clear_screen()
        print("PRESS ENTER TO BACK TO THE MENU!")
        print_usage()
        _ = input()
        self.menu()

    def run_client(self):
        if self.PROTOCOL == 'tcp':
            self.run_tcp_client()
        elif self.PROTOCOL == 'udp':
            self.RESOLUTION = (320, 240)
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
        self.define_tcp_server()
        self.tcp_start_server()

        while True:
            try:
                frame = self.receive_from_rpi()
                ready_image = self.decode_image(frame)
                self.show_image(ready_image)

            except KeyboardInterrupt:
                self.destroy_window()
                break

    def run_tcp_server(self):
        self.define_tcp_client()
        self.tcp_connect_to_server()

        self.set_camera()

        while True:
            try:
                frame = self.read_frame()
                resized = self.resize_frame(frame)
                encoded = self.encode_image(resized)
                self.tcp_send_data(encoded)

            except KeyboardInterrupt:
                self.release_camera()
                self.destroy_window()
                break

    def run_udp_client(self):
        self.set_camera()
        self.define_udp_client()
        self.udp_connect_to_server()

        while True:
            frame = self.read_frame()
            resized = self.resize_frame(frame)
            encoded = self.encode_image(resized)
            self.udp_send_data(encoded)

    def run_udp_server(self):
        self.define_udp_server()
        self.udp_start_server()

        while True:
            data = self.udp_receive_data()
            read_image = self.decode_image(data)
            self.show_image(read_image)
