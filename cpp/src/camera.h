//
// Created by mateusz on 23.11.18.
//

#ifndef VIDEOSTREAM_CAMERA_H
#define VIDEOSTREAM_CAMERA_H

#include <opencv2/opencv.hpp>
#include "operation.h"

#define COLUMNS 640
#define ROWS 480

class camera {
public:
    camera();

private:
    cv::VideoCapture* cameraObject;
    cv::Mat* imageToReceive;

public:
    cv::Mat captureImage();
    cv::Mat cropImage(cv::Mat&);
    size_t getImageSize(cv::Mat&) const;
    cv::Mat* getImageToReceive() const;
    int getImageLength(unsigned char *);
    std::string encodeData(cv::Mat&);
    cv::Mat decodeData(std::string);

};


#endif // VIDEOSTREAM_CAMERA_H
