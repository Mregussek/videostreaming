//
// Created by mateusz on 23.11.18.
//

#ifndef VIDEOSTREAM_CAMERA_H
#define VIDEOSTREAM_CAMERA_H

#include <opencv2/opencv.hpp>
#include "operation.h"

#define COLUMNS 640
#define ROWS 480

class Camera {
public:
    Camera();

private:
    cv::VideoCapture* cameraObject;
public:
    cv::Mat* imageToReceive;

    cv::Mat captureImage();
    cv::Mat cropImage(cv::Mat&);
    size_t getImageSize(cv::Mat&) const;
    std::string encodeData(cv::Mat&);
    void showImage();
};


#endif // VIDEOSTREAM_CAMERA_H
