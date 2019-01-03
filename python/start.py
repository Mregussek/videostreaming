
print("Checking if all packages can be imported")
meter = 0

try:
    import cv2
except:
    meter += 1
    print("Cannot import cv2 for managing camera")

try:
    import zmq
except:
    meter += 1
    print("Cannot import zmq for networking")

try:
    import netifaces
except:
    meter += 1
    print("Cannot import netifaces for getting valid IP addresses")

try:
    import time
except:
    meter += 1
    print("Cannot import time for clearance in menu")

try:
    import os
except:
    meter += 1
    print("Cannot import os (???)")

try:
    import base64
except:
    meter += 1
    print("Cannot import base64 for encoding / decoding image")

try:
    import numpy
except:
    meter += 1
    print("Cannot import numpy for converting data")

if meter > 0:
    print("Cannot run!")
    time.sleep(2)
    exit(0)
else:
    print("All packages are installed!")
    time.sleep(2)
    from src.main import Main
    obj = Main()
    obj.menu()