from src.network import Network
from src.camera import Camera

camera = Camera()
client = Network()
client.set_ip('127.0.0.1')

client.define_client()
client.connect()

while True:
    received = client.receive_normal(2048000)
    converted = Camera.convert_image(received)
    ready_image = camera.reshape(converted)
    Camera.show_image(ready_image)
    key = Camera.maybe_end()

    if key == 27:
        client.send_data(b'end')
        break
    else:
        client.send_data(b'continue')
