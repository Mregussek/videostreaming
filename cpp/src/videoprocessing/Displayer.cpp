//
// Created by mateusz on 23.04.19.
//

#include "Displayer.h"

namespace mrz
{
    Displayer::Displayer() :
    image(new cv::Mat( cv::Mat::zeros(480, 640, CV_8UC1) )),
    image_size( new size_t(image->total() * image->elemSize()) ),
    key( new int() )
    {
        image_metadata = image ->data;
    }

    Displayer::~Displayer()
    {
        delete image;
        delete image_size;
        delete key;
    }

    void Displayer::if_continuous()
    {
        if( image ->isContinuous() )
            *image = image ->clone();
    }

    int Displayer::wait()
    {
        *key = cv::waitKey(10);
        return *key;
    }

    void Displayer::show_image()
    {
        cv::imshow("Video Streaming", *image);
    }
}