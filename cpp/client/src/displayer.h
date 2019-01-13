#ifndef VIDEOSTREAM_DISPLAYER_H
#define VIDEOSTREAM_DISPLAYER_H

#include <opencv2/opencv.hpp>

class Displayer {
    cv::Mat image;
    size_t imageSize;
    int key;

public:

    Displayer();
    void checkIfContinuous();
    size_t getImageSize();
    void createWindow();
    int getKey();
    int wait();
    uchar* getMetadata();
    void showImage();
};


#endif //VIDEOSTREAM_DISPLAYER_H
