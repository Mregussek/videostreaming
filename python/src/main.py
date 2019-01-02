from .network import Network
from .camera import Camera
from .test import user_selects_ip
from .test import user_selects_protocol
#import usage
import os
import time


def clear_screen():
    os.system('cls' if os.name == 'nt' else 'clear')

def print_usage():
    tcp = """ 
For better usage my proposal for TCP protocol is start with
creating server (which is 2 option in menu). App will wait for
correctly configured client and accept connection without 
athourization. Then you should see a window with video from server. """

    udp = """UDP on the other hand is much more complicated for me. For
better experience I propose you firstly run a client (1 option)
on the client machine. It will start waiting for data and if you
run a server it will open a window for video streaming."""
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
        print("Server: {} {} {}".format(self.SERVER_IP, self.PORT, self.PROTOCOL))
        print("Client: {} {} {}".format(self.CLIENT_IP, self.PORT, self.PROTOCOL))
        print("-"*28)
        print("1. Start watching")
        print("2. Run Server")
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
        print("1. Change IP for server ({})".format(self.SERVER_IP))
        print("2. Change IP for client ({})".format(self.CLIENT_IP))
        print("3. Change Port number ({})".format(self.PORT))
        print("4. Change protocol ({})".format(self.PROTOCOL))
        print("5. Back")
        choice = input("> ")

        if choice == '1':
            clear_screen()
            print("Your IP for server is: {}".format(self.SERVER_IP))

            ip = user_selects_ip()
            print("Changed successfully!")
            self.set_server_ip(ip)
            time.sleep(1)
            self.configure()

        elif choice == '2':
            clear_screen()
            print("Your IP for client is: {}".format(self.CLIENT_IP))

            self.set_client_ip()
            time.sleep(1)
            self.configure()

        elif choice == '3':
            clear_screen()

            print("You PORT number is: {}".format(self.PORT))
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
            received = self.receive_tcp(2048000)
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
            if not self.is_someone_connected:
                self.accept_connection_tcp()

            frame = self.read_frame()
            frame_str = frame.tostring()
            self.send_data_tcp(frame_str)
            self.receive_end_tcp(1024)

            key = Camera.maybe_end()
            if key == 27:
                break

        self.release_camera()
        self.shutdown_server()

    def run_udp_client(self):
        self.define_client_udp()
        self.set_camera()

        while True:
            frame = self.read_frame()
            #frame_flatten = frame.flatten()
            frame_str = frame.tostring()

            for i in range(20):
                frame_part = frame_str[i*46080:(i+1)*46080]
                self.send_data_udp(frame_part)

            key = Camera.maybe_end()
            if key == 27:
                break

    def run_udp_server(self):
        self.define_server_udp()
        self.start_server_udp()

        while True:
            self.receive_normal_udp(46080)

            if len(self.udp_receiver) == (46080*20):
                converted = Camera.convert_image(self.udp_receiver)
                ready_image = self.reshape(converted)
                Camera.show_image(ready_image)
                self.udp_receiver = b''

            key = Camera.maybe_end()
            if key == 27:
                break
