# Takes photo using the picamera module
# Made by Mateusz Rzeczyca.

from picamera import PiCamera
from time import sleep

cam = PiCamera()

columns = 640
rows = 480
resolution = (columns, rows)

cam.resolution = resolution

# Warm-up for camera
cam.start_preview()
sleep(2)

camera.capture('rpiPhoto.jpg')