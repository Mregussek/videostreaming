# Video Streaming with Picamera
# made by Mateusz Rzeczyca

import socket
import picamera
import time

# get connection
serverSocket = socket.socket(socket.AF_INET, 
                        socket.SOCK_STREAM)
address = ("192.168.137.1", 3305)
serverSocket.connect(address)

print("Connected!")

connection = serverSocket.makefile('wb')

camera = picamera.PiCamera()

try:
    with picamera.PiCamera() as camera:
        camera.resolution = (640, 480)
        camera.framerate = 10
        
        #camera.start_preview()
        #time.sleep(2)

        camera.start_recording(connection, format='h264')
        camera.wait_recording(60)
        camera.stop_recording()
finally:
    connection.close()
    serverSocket.close()