//
// Created by mateusz on 23.11.18.
//

#include <opencv2/opencv.hpp>
#include <memory>
#include "camera.h"

camera::camera()
        : cameraObject( cv::VideoCapture(0) ),
          imageToReceive( cv::Mat::zeros(COLUMNS, ROWS, CV_8UC3) )
{

}

cv::Mat camera::captureImage()
{
    cv::Mat capture;
    this ->cameraObject >> capture;

    return capture;
}

bool camera::checkImage(cv::Mat &image)
{
    bool isThereImage = this ->cameraObject.read(image);

    return isThereImage;
}

void camera::cropImage(cv::Mat& imageToCrop)
{
    imageToCrop = imageToCrop.reshape(0, 1);
}

size_t camera::getImageSize(cv::Mat& image) const
{
    size_t imgSize = image.total() * image.elemSize();
    return imgSize;
}

cv::Mat camera::getImageToReceive() const
{
    return this ->imageToReceive;
}

