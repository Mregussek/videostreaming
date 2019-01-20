#include "Camera.h"

Camera::Camera()
{
    this ->camera = cv::VideoCapture(0);
    this ->image = cv::Mat::zeros(480 , 640, CV_8UC1);
    this ->imageSize = this ->image.total() * this ->image.elemSize();
}

void Camera::checkContinuous()
{
    if (! (this ->image.isContinuous()) )
    {
        this->image = this->image.clone();
        this->grayImage = this->image.clone();
    }
}

size_t Camera::getImageSize()
{
    return this ->imageSize;
}

bool Camera::readFrame()
{
    this ->camera >> this ->image;

    if(!image.data)
        return false;

    return true;
}

void Camera::proccessImage()
{
    cvtColor(this ->image, this ->grayImage, cv::COLOR_BGR2GRAY);
}
