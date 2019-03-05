/*

Written by Mateusz Rzeczyca.
Student - AGH University of Science and Technology
info@mateuszrzeczyca.pl
20.01.2019

*/

#ifndef VIDEOSTREAM_CAMERA_H
#define VIDEOSTREAM_CAMERA_H

#include <opencv2/opencv.hpp>

class Camera {
    cv::VideoCapture camera;
    cv::Mat image;
    size_t imageSize;

public:
    cv::Mat grayImage;
    Camera();
    void checkContinuous();
    size_t getImageSize();
    bool readFrame();
    void proccessImage();

};


#endif //VIDEOSTREAM_CAMERA_H
