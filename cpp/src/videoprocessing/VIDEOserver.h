//
// Created by mateusz on 18.03.19.
//

#ifndef VIDEOSTREAMING_VIDEOSERVER_H
#define VIDEOSTREAMING_VIDEOSERVER_H

#include "VIDEO.h"

namespace mrz
{
    class VIDEOserver;
}

class mrz::VIDEOserver : public mrz::VIDEO {
public:
    VIDEOserver();

    void check_if_continuous() override;
    size_t get_image_size() override;
    void create_window() override;
    int get_key() override;
    int wait() override;
    uchar* get_metadata() override;
    void show_image() override;

    // for inheriting
    bool read_frame() override { return false; }
    void process_image() override { return; }

private:
    cv::Mat image;
    size_t image_size;
    int key;
};


#endif //VIDEOSTREAMING_VIDEOSERVER_H
