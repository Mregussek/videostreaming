#!usr/bin/env python
# Written by Mateusz Rzeczyca

import cv2


class Camera(object):
    def __init__(self):
        self.cameraObject = cv2.VideoCapture(0)

    def read_frame(self):
        frame = self.cameraObject.read()
        return frame

    @staticmethod
    def decode_image(image):
        decoded = cv2.imdecode(image)
        return decoded

    @staticmethod
    def encode_image(image):
        encoded = cv2.imencode(image)
        return encoded

    @staticmethod
    def show_image(image):
        cv2.imshow('WINDOW', image)
