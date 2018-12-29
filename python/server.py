import socket
import cv2

from src.network import Network
from src.camera import Camera

server = Network()
camera = Camera()
#IP = ''
#PORT = 3305
#ADDRESS = (IP, PORT)
#HEIGHT = 480
#WIDTH = 640


server.define_tcp()
server.start_server()
#server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#server_socket.bind(ADDRESS)
#server_socket.listen(1)

camera.set_camera()
#camera = cv2.VideoCapture(0)
#camera.set(cv2.CAP_PROP_FRAME_HEIGHT, HEIGHT)
#camera.set(cv2.CAP_PROP_FRAME_WIDTH, WIDTH)

#client_socket = None

while True:
    server.accept_connection()
    #if client_socket is None:
        #client_socket, _ = server_socket.accept()

    frame = camera.read_frame()
    #_, image = camera.read()
    #data = image.tostring()

    server.send_data(frame)
    #try:
    #    client_socket.send(data)
    #except Exception:
    #    pass

    received = server.receive_end(1024)
    server.test_if_end(received)
    #try:
    #    receive = client_socket.recv(1024)
    #    if receive == 'end':
    #        client_socket.close()
    #        client_socket = None
    #        break
    #except:
    #    client_socket.close()
    #    client_socket = None

Camera.release_camera()
server.shutdown()
#cv2.VideoCapture(0).release()
#server_socket.close()
