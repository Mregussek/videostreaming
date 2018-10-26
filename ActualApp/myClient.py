# Video Streaming with Picamera
# made by Mateusz Rzeczyca
# this file run on RPi

import socket
import picamera
import time
import io
import struct

# get connection
serverSocket = socket.socket(socket.AF_INET, 
                        socket.SOCK_STREAM)
address = ("192.168.137.1", 3305)
serverSocket.connect(address)

connection = serverSocket.makefile('wb')

try:
    with picamera.PiCamera() as camera:
        # camera configuration
        camera.resolution = (640, 480)
        camera.framerate = 30

        # warm-up for camera
        time.sleep(2)
        start = time.time()

        count = 0
        stream = io.BytesIO()

        for foo in camera.capture_continuous(stream, 'jpeg',
                                             use_video_port=True):
            connection.write( struct.pack('<L', stream.tell() ))
            connection.flush()

            stream.seek(0)
            connection.write(stream.read())
            count += 1

            if time.time() - start > 30:
                break

            stream.seek(0)
            stream.truncate()

    connection.write(struct.pack('<L', 0))
finally:
    connection.close()
    serverSocket.close()
    finish = time.time()
    
print('Sent %d images in %d seconds at %.2ffps' % (
    count, finish-start, count / (finish-start)))
