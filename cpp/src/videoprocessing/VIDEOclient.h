//
// Created by mateusz on 18.03.19.
//

#ifndef VIDEOSTREAMING_VIDEOCLIENT_H
#define VIDEOSTREAMING_VIDEOCLIENT_H

#include "VIDEO.h"

namespace mrz
{
    class VIDEOclient;
}

class mrz::VIDEOclient : public mrz::VIDEO {
public:
    VIDEOclient();

    void check_if_continuous() override;
    size_t get_image_size() override;
    bool read_frame() override;
    void process_image() override;

    // for inheriting
    void create_window() override { return; }
    int get_key() override { return 0; }
    int wait() override { return 0; }
    uchar* get_metadata() override { return nullptr; }
    void show_image() override { return; }

    bool got_frame;
    cv::Mat gray_image;
private:
    cv::VideoCapture camera;
    cv::Mat image;
    size_t image_size;
};



#endif //VIDEOSTREAMING_VIDEOCLIENT_H
