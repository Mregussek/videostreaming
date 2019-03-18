//
// Created by mateusz on 16.03.19.
//

#ifndef VIDEOSTREAMING_VIDEO_H
#define VIDEOSTREAMING_VIDEO_H

#include "../inc_def.h"

namespace mrz
{
    class VIDEO
    {
        virtual void check_if_continuous() = 0;
        virtual size_t get_image_size() = 0;

        // for client
        virtual bool read_frame() = 0;
        virtual void process_image() = 0;

        // for server
        virtual void create_window() = 0;
        virtual int get_key() = 0;
        virtual int wait() = 0;
        virtual uchar* get_metadata() = 0;
        virtual void show_image() = 0;
    };
}

#endif //VIDEOSTREAMING_VIDEO_H
