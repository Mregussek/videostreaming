//
// Created by mateusz on 25.11.18.
//

#ifndef VIDEOSTREAM_CAMERAPOINTERS_H
#define VIDEOSTREAM_CAMERAPOINTERS_H

#include <memory>
#include <opencv2/opencv.hpp>

#define COLUMNS 640
#define ROWS 480

class cameraPointers {
public:
    cameraPointers();

private:
    std::unique_ptr<cv::VideoCapture> cameraObject;
    std::shared_ptr<cv::Mat> imageToReceive;
    std::shared_ptr<cv::Mat> croppedImage;


public:
    void getImage(std::shared_ptr<cv::Mat>);
    void cropImage(std::shared_ptr<cv::Mat>);
    size_t getImageSize(std::shared_ptr<cv::Mat>&) const;
    std::shared_ptr<cv::Mat> getImageToReceive() const;
};


#endif //VIDEOSTREAM_CAMERAPOINTERS_H
