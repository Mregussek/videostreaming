//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   30.03.2019

#ifndef VIDEOSTREAMING_DISPLAYER_H
#define VIDEOSTREAMING_DISPLAYER_H

#include "Strategy.h"

namespace mrz
{
    class Displayer{
    public:
        Displayer();
        ~Displayer();

        void check_if_continuous();
        size_t* get_image_size();
        int get_key();
        int wait();
        uchar* get_metadata();
        void show_image();

    private:
        cv::Mat* image;
        size_t* image_size;
        int* key;
    };
}

#endif //VIDEOSTREAMING_DISPLAYER_H