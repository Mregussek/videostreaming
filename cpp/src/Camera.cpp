//
// Created by mateusz on 23.11.18.
//

#include <opencv2/opencv.hpp>
#include "Camera.h"

Camera::Camera()
{
    *cameraObject = cv::VideoCapture(0);
    *imageToReceive = cv::Mat::zeros(ROWS, COLUMNS, CV_8UC1);
}

cv::Mat Camera::captureImage()
{
    cv::Mat capture;
    *cameraObject >> capture;

    bool isThereImage = cameraObject ->read(capture);
    if(!isThereImage)
        // throw("Cannot capture image!");
        exit(0);

    return capture;
}

cv::Mat Camera::cropImage(cv::Mat& imageToCrop)
{
    imageToCrop = imageToCrop.reshape(0, 1);

    return imageToCrop;
}

size_t Camera::getImageSize(cv::Mat& image) const
{
    size_t imgSize = image.total() * image.elemSize();
    return imgSize;
}

std::string Camera::encodeData(cv::Mat& image)
{
    cv::Mat encoded = cv::imdecode(image, 0);
    std::string encodedString(encoded.begin<unsigned char>(), encoded.end<unsigned char>());

    return encodedString;
}

void Camera::showImage()
{
    cv::imshow("videoStream", *imageToReceive);
}