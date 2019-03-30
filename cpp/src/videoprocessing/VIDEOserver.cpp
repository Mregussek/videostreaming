//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   30.03.2019

#include "VIDEOserver.h"

namespace mrz
{
    VIDEOserver::VIDEOserver() :
    image( cv::Mat::zeros(480, 640, CV_8UC1) ),
    image_size( image.total() * image.elemSize() )
    {}

    void VIDEOserver::check_if_continuous()
    {
        if( this ->image.isContinuous() )
            this ->image = this ->image.clone();
    }

    size_t& VIDEOserver::get_image_size()
    {
        return this ->image_size;
    }

    void VIDEOserver::create_window()
    {
        cv::namedWindow("Video Stream", 1);
    }

    int VIDEOserver::get_key()
    {
        return this ->key;
    }

    int VIDEOserver::wait()
    {
        this ->key = cv::waitKey(10);
        return this ->key;
    }

    uchar* VIDEOserver::get_metadata()
    {
        return this ->image.data;
    }

    void VIDEOserver::show_image()
    {
        cv::imshow("Video Streaming", this ->image);
    }
}