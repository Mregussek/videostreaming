This is video streaming app, which was written for streaming video from
Raspberry Pi to client machine. For this I have prepared 3 programs for
comparison in C++, Python and quick commands in bash.

Of course you can use this app to work with another WebCam, other than RPi.
Package for getting frames is OpenCV so it should work correctly only when you
have it installed.

Observations:
Since I used only Python for streaming data, I have seen that this app
sometimes losses data. For checking this up I have written scripts in bash. It runs correctly. My charger has low voltage to make RPi run correctly. Now I am using another one to keep it better.

C++ Explanation:

Python:
    For TCP in Python I have used 640x480 resolution. It can work without any problems.
    On the other hand UDP is set to 320x240 in order to send data properly.

    Possible bugs:
        1. Cannot open PiCamera by the 0 index.
         It may happen, because for this project I used OpenCV. Creating camera-like object by cv2.VideoCapture(0) don't recognize PiCamera so, you must enable it manually:

         sudo modprobe bcm2835-v4l2

Bash Explanation:

Written by Mateusz Rzeczyca.
Student - AGH University of Science and Technology
info@mateuszrzeczyca.pl
04.01.2019