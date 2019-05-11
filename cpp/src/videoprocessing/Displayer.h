//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   30.03.2019

#ifndef VIDEOSTREAMING_DISPLAYER_H
#define VIDEOSTREAMING_DISPLAYER_H

#include "Strategy.h"

namespace mrz
{
    class Displayer {
    public:
        Displayer();
        Displayer(int, char*);
        ~Displayer();

        void check_if_continuous();
        size_t* get_image_size();
        void decode_image();
        int wait();
        uchar* get_metadata();
        void show_image();

        int* key;
    private:
        cv::Mat* raw_data;
        cv::Mat* image;
        size_t* image_size;
    };
}

#endif //VIDEOSTREAMING_DISPLAYER_H