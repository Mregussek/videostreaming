
//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   30.03.2019

#include "Camera.h"

namespace mrz
{
    Camera::Camera() :
    camera( cv::VideoCapture(0) ),
    image( cv::Mat::zeros(480, 640, CV_8UC1)),
    image_size( image.total() * image.elemSize() ),
    got_frame( false )
    {}

    void Camera::check_if_continuous()
    {
        if(! (this ->image.isContinuous()) )
        {
            this ->image = this ->image.clone();
            this ->gray_image = this ->image.clone();
        }
    }

    size_t& Camera::get_image_size()
    {
        return this ->image_size;
    }

    bool Camera::read_frame()
    {
        this ->camera >> this ->image;

        if(!image.data)
            return false;

        return true;
    }

    void Camera::process_image()
    {
        cv::cvtColor(this ->image, this ->gray_image, cv::COLOR_BGR2GRAY);
    }
}