//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   30.03.2019

#ifndef VIDEOSTREAMING_VIDEOCLIENT_H
#define VIDEOSTREAMING_VIDEOCLIENT_H

#include "../inc_def.h"

namespace mrz
{
    class VIDEOclient;
}

class mrz::VIDEOclient {
public:
    VIDEOclient();

    void check_if_continuous();
    size_t& get_image_size();
    bool read_frame();
    void process_image();

    bool got_frame;
    cv::Mat gray_image;
private:
    cv::VideoCapture camera;
    cv::Mat image;
    size_t image_size;
};



#endif //VIDEOSTREAMING_VIDEOCLIENT_H
