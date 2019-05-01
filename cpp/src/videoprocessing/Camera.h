//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   30.03.2019

#ifndef VIDEOSTREAMING_CAMERA_H
#define VIDEOSTREAMING_CAMERA_H

#include "Strategy.h"

namespace mrz
{
    class Camera {
    public:
        Camera();

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
}



#endif //VIDEOSTREAMING_CAMERA_H