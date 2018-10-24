# Video Streaming with Picamera
# made by Mateusz Rzeczyca

import socket
import picamera
import time
import struct
import io

# get connection
serverSocket = socket.socket(socket.AF_INET, 
                        socket.SOCK_STREAM)
address = ("192.168.43.70", 3305)
serverSocket.connect(address)

print("Connected!")

connection = serverSocket.makefile('wb')

camera = picamera.PiCamera()

# camera configuration
camera.resolution = (640, 480)
camera.framerate = 10

# timing for stream
time.sleep(1)
start = time.time()

# create object for getting bytes in stream
stream = io.BytesIO()

count = 0

for nothing in camera.capture_continuous(stream, 'jpeg',
                            use_video_port = True):
    currentPosition = stream.tell()
    
    # return written bytes of stream
    connection.write( struct.pack('<L', currentPosition))
    
    # flush write buffers
    connection.flush()

    # change stream position to beginining
    stream.seek(0)
    connection.write( stream.read() )
    count += 1

    if time.time() - start > 30:
        break

    # clear buffer and begin again
    stream.seek(0)
    stream.truncate()

connection.write( struct.pack('<L', 0) )

connection.close()
serverSocket.close()