//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   30.03.2019

#include "Displayer.h"

namespace mrz
{
    Displayer::Displayer() :
    image( cv::Mat::zeros(480, 640, CV_8UC1) ),
    image_size( image.total() * image.elemSize() )
    {}

    void Displayer::check_if_continuous()
    {
        if( this ->image.isContinuous() )
            this ->image = this ->image.clone();
    }

    size_t& Displayer::get_image_size()
    {
        return this ->image_size;
    }

    int Displayer::get_key()
    {
        return this ->key;
    }

    int Displayer::wait()
    {
        this ->key = cv::waitKey(10);
        return this ->key;
    }

    uchar* Displayer::get_metadata()
    {
        return this ->image.data;
    }

    void Displayer::show_image()
    {
        cv::imshow("Video Streaming", this ->image);
    }
}