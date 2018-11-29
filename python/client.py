#!/usr/bin/env python
# -*- coding: utf-8 -*-

import cv2
import socket
import base64
import numpy as np

IP_SERVER = "127.0.0.1"
PORT_SERVER = 3305
TIMEOUT_SOCKET = 10
SIZE_PACKAGE = 4096

IMAGE_HEIGHT = 480
IMAGE_WIDTH = 640
COLOR_PIXEL = 3  # RGB

connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
connection.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
connection.settimeout(TIMEOUT_SOCKET)
connection.connect((IP_SERVER, PORT_SERVER))

while True:
    fileDescriptor = connection.makefile('rb')
    result = fileDescriptor.readline()
    fileDescriptor.close()
    result = base64.b64decode(result)

    frame = np.fromstring(result, dtype=np.uint8)
    frame_matrix = np.array(frame)
    frame_matrix = np.reshape(frame_matrix, (IMAGE_HEIGHT, IMAGE_WIDTH, COLOR_PIXEL))
    cv2.imshow('Window title', frame_matrix)

    if cv2.waitKey(5) & 0xFF == ord('q'):
        break

connection.close()
