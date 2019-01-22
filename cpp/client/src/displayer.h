/*

Written by Mateusz Rzeczyca.
Student - AGH University of Science and Technology
info@mateuszrzeczyca.pl
20.01.2019

*/

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
