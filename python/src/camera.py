#!usr/bin/env python
# Written by Mateusz Rzeczyca

import cv2


class Camera(object):
    def __init__(self):
        self.cameraObject = cv2.VideoCapture(0)
        self.resolution = (480, 640, 3)

    def set_camera(self):
        self.cameraObject.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
        self.cameraObject.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

    def read_frame(self):
        is_there_frame, frame = self.cameraObject.read()

        if not is_there_frame:
            exit(0)

        return frame

    def close_camera(self):
        self.cameraObject.release()

    @staticmethod
    def decode_image(image):
        decoded = cv2.imdecode(image, cv2.IMREAD_COLOR)
        return decoded

    @staticmethod
    def encode_image(image):
        encoded = cv2.imencode('.jpg', image)[1].tostring()
        return encoded

    @staticmethod
    def show_image(image):
        cv2.imshow('WINDOW', image)
