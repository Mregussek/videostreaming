print("Checking if all packages can be imported")
meter = 0

try:
    import cv2
except:
    meter += 1
    print("Cannot import cv2 for managing camera")

try:
    import socket
except:
    meter += 1
    print("Cannot import socket for networking")

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

if meter > 0:
    print("Cannot run!")
    time.sleep(2)
else:
    print("All packages are installed!")
    time.sleep(2)
    from src.main import Main
    obj = Main()
    obj.menu()
