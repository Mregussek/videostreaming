//
// Created by mateusz on 23.11.18.
//

#include <opencv2/opencv.hpp>
#include "camera.h"

camera::camera()
{
    *cameraObject = cv::VideoCapture(0);
    *imageToReceive = cv::Mat::zeros(COLUMNS, ROWS, CV_8UC1);
}

cv::Mat camera::captureImage()
{
    cv::Mat capture;
    *cameraObject >> capture;

    bool isThereImage = cameraObject ->read(capture);
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

cv::Mat* camera::getImageToReceive() const
{
    return imageToReceive;
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
    cv::Mat encoded = cv::imdecode(image, 0);
    std::string encodedString(encoded.begin<unsigned char>(), encoded.end<unsigned char>());

    return encodedString;
}

cv::Mat camera::decodeData(std::string encoded)
{
    cv::Mat read = cv::imread(encoded, 0);
    cv::Mat decoded = cv::imdecode(read, 0);

    return decoded;
}