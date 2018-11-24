//
// Created by mateusz on 23.11.18.
//

#ifndef CLIENTRPI_CAMERA_H
#define CLIENTRPI_CAMERA_H

#include <opencv2/opencv.hpp>
#include <memory>

#define COLUMNS 640
#define ROWS 480

class camera {
public:
    camera();

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


#endif //CLIENTRPI_CAMERA_H
