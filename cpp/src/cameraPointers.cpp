//
// Created by mateusz on 23.11.18.
//

#include <opencv2/opencv.hpp>
#include <memory>
#include "cameraPointers.h"

cameraPointers::cameraPointers()
        : cameraObject( std::make_unique<cv::VideoCapture>(0) ),
          imageToReceive( std::make_unique<cv::Mat>( cv::Mat::zeros(COLUMNS, ROWS, CV_8UC3)) )
{

}

void cameraPointers::getImage(std::shared_ptr<cv::Mat> image)
{
    bool isThereImage = this ->cameraObject ->read(*image);

    if(!isThereImage)
        throw("Cannot get data from camera!");
}

void cameraPointers::cropImage(std::shared_ptr<cv::Mat> imageToCrop)
{
    cv::resize(*imageToCrop, *croppedImage, cv::Size(COLUMNS, ROWS) );
}

size_t cameraPointers::getImageSize(std::shared_ptr<cv::Mat>& image) const
{
    size_t imgSize = image ->total() * image ->elemSize();
    return imgSize;
}

std::shared_ptr<cv::Mat> cameraPointers::getImageToReceive() const
{
    return this ->imageToReceive;
}

