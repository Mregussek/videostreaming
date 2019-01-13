#ifndef VIDEOSTREAM_CAMERA_H
#define VIDEOSTREAM_CAMERA_H

#include <opencv2/opencv.hpp>

class Camera {
    cv::VideoCapture camera;
    cv::Mat image;
    size_t imageSize;

public:
    cv::Mat grayImage;
    Camera();
    void checkContinuous();
    size_t getImageSize();
    void readFrame();
    void proccessImage();

};


#endif //VIDEOSTREAM_CAMERA_H
