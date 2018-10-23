import io
import socket
import struct
import time
import threading
import picamera

client_socket = socket.socket()
client_socket.connect(('spider', 8000))
connection = client_socket.makefile('wb')
try:
    connection_lock = threading.Lock()
    pool_lock = threading.Lock()
    pool = []

    class ImageStreamer(threading.Thread):
        def __init__(self):
            super(ImageStreamer, self).__init__()
            self.stream = io.BytesIO()
            self.event = threading.Event()
            self.terminated = False
            self.start()

        def run(self):
            # This method runs in a background thread
            while not self.terminated:
                # Wait for the image to be written to the stream
                if self.event.wait(1):
                    try:
                        with connection_lock:
                            connection.write(struct.pack('<L', self.stream.tell()))
                            connection.flush()
                            self.stream.seek(0)
                            connection.write(self.stream.read())
                    finally:
                        self.stream.seek(0)
                        self.stream.truncate()
                        self.event.clear()
                        with pool_lock:
                            pool.append(self)

    count = 0
    start = time.time()
    finish = time.time()

    def streams():
        global count, finish
        while finish - start < 30:
            with pool_lock:
                if pool:
                    streamer = pool.pop()
                else:
                    streamer = None
            if streamer:
                yield streamer.stream
                streamer.event.set()
                count += 1
            else:
                # When the pool is starved, wait a while for it to refill
                time.sleep(0.1)
            finish = time.time()

    with picamera.PiCamera() as camera:
        pool = [ImageStreamer() for i in range(4)]
        camera.resolution = (640, 480)
        camera.framerate = 30
        time.sleep(2)
        start = time.time()
        camera.capture_sequence(streams(), 'jpeg', use_video_port=True)

    # Shut down the streamers in an orderly fashion
    while pool:
        streamer = pool.pop()
        streamer.terminated = True
        streamer.join()

    # Write the terminating 0-length to the connection to let the server
    # know we're done
    with connection_lock:
        connection.write(struct.pack('<L', 0))

finally:
    connection.close()
    client_socket.close()

print('Sent %d images in %d seconds at %.2ffps' % (
    count, finish-start, count / (finish-start)))