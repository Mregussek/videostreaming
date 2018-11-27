#!/usr/bin/env python
# -*- coding: utf-8 -*-
import cv2
import socket
import base64
from threading import Thread

SERVER_IP = "127.0.0.1"
SERVER_PORT = 3305
MAX_NUM_CONNECTIONS = 20
DEVICE_NUMBER = 0


class ConnectionPool(Thread):
    def __init__(self, ip_, port_, conn_, device_):
        Thread.__init__(self)
        self.ip = ip_
        self.port = port_
        self.conn = conn_
        self.device = device_
        print("New server socket thread started for " + self.ip + ":" + str(self.port) )

    def run(self):
        try:
            while True:
                ret, frame = self.device.read()
                data = frame.tostring()
                self.conn.sendall(base64.b64encode(data) + '\r\n')
        except:
            print ("Connection lost")
        self.conn.close()


camera = cv2.VideoCapture(DEVICE_NUMBER)
print ("Waiting connections...")

connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
connection.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
connection.bind((SERVER_IP, SERVER_PORT))
connection.listen(MAX_NUM_CONNECTIONS)

while True:
    (conn, (ip, port)) = connection.accept()
    thread = ConnectionPool(ip, port, conn, camera)
    thread.start()

connection.close()
camera.release()