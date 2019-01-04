"""

Written by Mateusz Rzeczyca.
Student - AGH University of Science and Technology
info@mateuszrzeczyca.pl
04.01.2019

"""

from picamera import PiCamera

columns = 640
rows = 480
resolution = (columns, rows)

cam = PiCamera()
cam.resolution = resolution

cam.start_recording("rpiVideo.h264")
cam.wait_recording(10)
cam.stop_recording()