//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   30.03.2019

#include "Camera.h"

namespace mrz
{
    Camera::Camera() :
    image( new cv::Mat( cv::Mat::zeros(480, 640, CV_8UC1)) ),
    gray_image( new cv::Mat() ),
    image_size( new size_t(image ->total() * image ->elemSize()) ),
    key( new int )
    {}

    Camera::~Camera()
    {
        delete camera;
        delete image;
        delete gray_image;
        delete image_size;
        delete key;
    }

    void Camera::open_camera()
    {
        camera = new cv::VideoCapture(0);

        if(! camera ->isOpened())
        {
            std::cerr << "Cannot open camera by 0 index!" << std::endl;
            exit(1);
        }
    }

    void Camera::check_if_continuous()
    {
        if(! (this ->image ->isContinuous()) )
        {
            *(this ->image) = this ->image ->clone();
            *(this ->gray_image) = this ->image ->clone();
        }
    }

    size_t* Camera::get_image_size()
    {
        return this ->image_size;
    }

    bool Camera::read_frame()
    {
        *(this ->camera) >> *(this ->image);

        if( image ->empty() )
        {
            std::cerr << "Frame data is empty!" << std::endl;
            return false;
        }

        return true;
    }

    void Camera::process_image()
    {
        cv::cvtColor(*(this ->image), *(this ->gray_image), cv::COLOR_BGR2GRAY);
    }

    void Camera::encode_image()
    {
        cv::resize(*image, *gray_image, cv::Size(640, 480), 0, 0, cv::INTER_LINEAR);
        std::vector<int> compression;
        compression.push_back(cv::IMWRITE_JPEG_QUALITY);
        compression.push_back(80);
        cv::imencode(".jpg", *gray_image, encoded, compression);
    }
}