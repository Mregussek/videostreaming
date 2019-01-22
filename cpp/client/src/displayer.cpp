/*

Written by Mateusz Rzeczyca.
Student - AGH University of Science and Technology
info@mateuszrzeczyca.pl
20.01.2019

*/

#include "displayer.h"

Displayer::Displayer()
{
    this ->image = cv::Mat::zeros(480 , 640, CV_8UC1);
    this ->imageSize = this ->image.total() * this ->image.elemSize();
}

void Displayer::checkIfContinuous()
{
    if(this ->image.isContinuous())
        this ->image = this ->image.clone();
}

size_t Displayer::getImageSize()
{
    return this ->imageSize;
}

void Displayer::createWindow()
{
    cv::namedWindow("RPI Video Stream", 1);
}

int Displayer::getKey()
{
    return this ->key;
}

int Displayer::wait()
{
    this ->key = cv::waitKey(10);
    return this ->key;
}

uchar* Displayer::getMetadata()
{
    return this ->image.data;
}

void Displayer::showImage()
{
    cv::imshow("RPI Video Stream", this ->image);
}