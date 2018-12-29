# Records video from RPi camera
# Made by Mateusz Rzeczyca

from picamera import PiCamera

columns = 640
rows = 480
resolution = (columns, rows)

cam = PiCamera()
cam.resolution = resolution

cam.start_recording("rpiVideo.h264")
cam.wait_recording(10)
cam.stop_recording()