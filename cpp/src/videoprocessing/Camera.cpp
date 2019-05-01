//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   30.03.2019

#include "Camera.h"

namespace mrz
{
    Camera::Camera() :
    camera( new cv::VideoCapture(0) ),
    image( new cv::Mat( cv::Mat::zeros(480, 640, CV_8UC1)) ),
    gray_image( new cv::Mat() ),
    image_size( new size_t(image ->total() * image ->elemSize()) ),
    got_frame( false )
    {}

    Camera::~Camera()
    {
        delete camera;
        delete image;
        delete gray_image;
        delete image_size;
    }

    void Camera::check_if_continuous()
    {
        if(! (this ->image ->isContinuous()) )
        {
            *(this ->image) = this ->image ->clone();
            *(this ->gray_image) = this ->image ->clone();
        }
    }

    size_t* Camera::get_image_size()
    {
        return this ->image_size;
    }

    bool Camera::read_frame()
    {
        *(this ->camera) >> *(this ->image);

        if(!image ->data)
            return false;

        return true;
    }

    void Camera::process_image()
    {
        cv::cvtColor(*(this ->image), *(this ->gray_image), cv::COLOR_BGR2GRAY);
    }
}