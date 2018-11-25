//
// Created by mateusz on 23.11.18.
//

#ifndef VIDEOSTREAM_CAMERA_H
#define VIDEOSTREAM_CAMERA_H

#include <opencv2/opencv.hpp>
#include <memory>

#define COLUMNS 640
#define ROWS 480

class camera {
public:
    camera();

private:
    cv::VideoCapture cameraObject;
    cv::Mat imageToReceive;
    cv::Mat croppedImage;


public:
    void getImage(cv::Mat&);
    void cropImage(cv::Mat&);
    size_t getImageSize(cv::Mat&) const;
    cv::Mat getImageToReceive() const;
};


#endif // VIDEOSTREAM_CAMERA_H
