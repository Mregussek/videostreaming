import cv2
import numpy as np
import base64


class Camera(object):
    def __init__(self):
        self.camera = None
        self.RESOLUTION = (640, 480)

    @staticmethod
    def encode_image(image):
        _, encoded = cv2.imencode('.jpg', image)
        as_text = base64.b64encode(encoded)
        return as_text

    @staticmethod
    def decode_image(data):
        decoded_b64 = base64.b64decode(data)
        from_string = np.fromstring(decoded_b64, dtype=np.uint8)
        decoded_cv2 = cv2.imdecode(from_string, 1)
        return decoded_cv2

    @staticmethod
    def show_image(image):
        cv2.imshow('RPi - Video Transmission', image)
        cv2.waitKey(1)

    @staticmethod
    def destroy_window():
        cv2.destroyAllWindows()

    def set_camera(self):
        self.camera = cv2.VideoCapture(0)

    def read_frame(self):
        is_there_frame, frame = self.camera.read()

        if not is_there_frame:
            print("Cannot read data from camera!")

        return frame

    def resize_frame(self, frame):
        res = cv2.resize(frame, self.RESOLUTION)
        return res

    def release_camera(self):
        self.camera.release()
