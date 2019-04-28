//
// Created by mateusz on 23.04.19.
//

#ifndef VIDEOSTREAMING_DISPLAYER_H
#define VIDEOSTREAMING_DISPLAYER_H

#include "Camera.h"

namespace mrz
{
    class Displayer
    {
    public:
        Displayer();
        ~Displayer();

        void if_continuous();
        void show_image();
        int wait();

        uchar* get_metadata();

        size_t* image_size;
        int* key;

    private:
        cv::Mat* image;
    };
}


#endif //VIDEOSTREAMING_DISPLAYER_H
