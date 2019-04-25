//
// Created by mateusz on 23.04.19.
//

#include "Camera.h"

namespace mrz
{
    Camera::Camera() :
    camera( new cv::VideoCapture(0) ),
    image( new cv::Mat( cv::Mat::zeros(480, 640, CV_8UC1) )),
    gray_image( new cv::Mat() ),
    image_size( new size_t(image ->total() * image ->elemSize()) )
    { }

    Camera::~Camera()
    {
        delete camera;
        delete image;
        delete gray_image;
        delete image_size;
    }

    void Camera::if_continuous()
    {
        if(! (image ->isContinuous() ))
        {
            *image = image ->clone();
            *gray_image = image ->clone();
        }
    }

    void Camera::read_frame()
    {
        *camera >> *image;

        if(! image ->data)
            //handle_read_frame();
            exit(1);
    }

    void Camera::process_frame()
    {
        cv::cvtColor(*image, *gray_image, cv::COLOR_BGR2GRAY);
    }
}