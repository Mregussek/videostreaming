//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   30.03.2019

#include "VIDEOclient.h"

namespace mrz
{
    VIDEOclient::VIDEOclient() :
    camera( cv::VideoCapture(0) ),
    image( cv::Mat::zeros(480, 640, CV_8UC1)),
    image_size( image.total() * image.elemSize() ),
    got_frame( false )
    {}

    void VIDEOclient::check_if_continuous()
    {
        if(! (this ->image.isContinuous()) )
        {
            this ->image = this ->image.clone();
            this ->gray_image = this ->image.clone();
        }
    }

    size_t& VIDEOclient::get_image_size()
    {
        return this ->image_size;
    }

    bool VIDEOclient::read_frame()
    {
        this ->camera >> this ->image;

        if(! image.data)
            return false;

        return true;
    }

    void VIDEOclient::process_image()
    {
        cv::cvtColor(this ->image, this ->gray_image, cv::COLOR_BGR2GRAY);
    }
}