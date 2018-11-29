//
// Created by mateusz on 23.11.18.
//

#include <opencv2/opencv.hpp>
#include <memory>
#include "camera.h"
#include "base64.h"

camera::camera()
: cameraObject( cv::VideoCapture(0) ),
    imageToReceive( cv::Mat::zeros(COLUMNS, ROWS, CV_8UC1) )
{

}

cv::Mat camera::captureImage()
{
    cv::Mat capture;
    this ->cameraObject >> capture;

    bool isThereImage = this ->cameraObject.read(capture);
    if(!isThereImage)
        // throw("Cannot capture image!");
        exit(0);

    return capture;
}

cv::Mat camera::cropImage(cv::Mat& imageToCrop)
{
    imageToCrop = imageToCrop.reshape(0, 1);

    return imageToCrop;
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

int camera::getImageLength(unsigned char * data)
{
    int result = 0;

    for(int i = 0; data[i] != '\0'; i++)
        result++;

    return result;
}

std::string camera::encodeData(cv::Mat& image)
{
    //std::vector<unsigned char> buffer;
    //cv::imencode(".jpg", image, buffer);
    //auto encodedChar = new unsigned char[buffer.size()];

    //for(int i = 0; i < buffer.size(); i++)
        //encodedChar[i] = buffer[i];

    //std::string encodedString = base64_encode(encodedChar, (unsigned int) buffer.size());
    std::string encodedString = base64_encode(image.data, COLUMNS * ROWS);

    return encodedString;
}

cv::Mat camera::decodeData(std::string encoded)
{
    cv::Mat image(COLUMNS, ROWS, CV_8UC1, encoded.data());
    return image;
}