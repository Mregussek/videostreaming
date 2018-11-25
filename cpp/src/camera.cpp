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

void camera::getImage(cv::Mat& image)
{
    bool isThereImage = this ->cameraObject.read(image);

    if(!isThereImage)
        throw("Cannot get data from camera!");
}

void camera::cropImage(cv::Mat& imageToCrop)
{
    cv::resize(imageToCrop, this ->croppedImage, cv::Size(COLUMNS, ROWS) );
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

