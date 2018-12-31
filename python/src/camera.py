import cv2
import numpy as np


class Camera(object):
    def __init__(self):
        self.camera = None
        self.HEIGHT = 480
        self.WIDTH = 640
        self.CHANNELS = 3
        self.RESOLUTION = (self.HEIGHT, self.WIDTH, self.CHANNELS)

    @staticmethod
    def show_image(image):
        cv2.imshow("VideoStreamRPi", image)

    @staticmethod
    def convert_image(image):
        converted = np.fromstring(image, dtype=np.uint8)
        return converted

    @staticmethod
    def maybe_end():
        key = cv2.waitKey(10)
        return key

    def set_camera(self):
        self.camera = cv2.VideoCapture(0)
        self.camera.set(cv2.CAP_PROP_FRAME_HEIGHT, self.HEIGHT)
        self.camera.set(cv2.CAP_PROP_FRAME_WIDTH, self.WIDTH)

    def read_frame(self):
        is_there_frame, frame = self.camera.read()

        if not is_there_frame:
            exit(0)

        return frame

    def reshape(self, image):
        try:
            reshaped = np.reshape(image, self.RESOLUTION)
        except Exception:
            reshaped = np.zeros(self.RESOLUTION)

        return reshaped

    def release_camera(self):
        self.camera.release()

