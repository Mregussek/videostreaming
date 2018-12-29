from src.network import Network
from src.camera import Camera

server = Network()
server.define_server()
server.start_server()

camera = Camera()
camera.set_camera()

while True:
    server.accept_connection()
    frame = camera.read_frame()
    server.send_data(frame)
    server.receive_end(1024)

Camera.release_camera()
server.shutdown()
