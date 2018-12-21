#!usr/bin/env python
# Written by Mateusz Rzeczyca

import cv2


class Camera(object):
    def __init__(self):
        self.cameraObject = cv2.VideoCapture(0)
        self.data = b''

    def read_frame(self):
        is_there_frame, frame = self.cameraObject.read()

        if not is_there_frame:
            exit(0)

        return frame

    @staticmethod
    def decode_image(image):
        decoded = cv2.imdecode(image, 1)
        return decoded

    @staticmethod
    def encode_image(image):
        encoded = cv2.imencode('.jpg', image)[1].tostring()
        return encoded

    @staticmethod
    def show_image(image):
        cv2.imshow('WINDOW', image)
