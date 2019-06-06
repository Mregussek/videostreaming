//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   rzeczyca@student.agh.edu.pl
//   30.03.2019

#ifndef VIDEOSTREAMING_CAMERA_H
#define VIDEOSTREAMING_CAMERA_H

#include "Displayer.h"

namespace mrz
{
    /**
     * Implements camera support
     */
    class Camera
    {
    public:
        cv::Mat* gray_image;
        std::vector<uchar> encoded;
        int* key;
    private:
        cv::VideoCapture* camera;
        cv::Mat* image;
        size_t* image_size;

    public:
        /**
         * Initializes the most important elements
         */
        Camera();
        /**
         * Deallocates memory
         */
        ~Camera();

        /**
         * Opens camera with 0 index
         */
        void open_camera();

        /**
         * Checks the matrix elements, if they are stored continuously without gaps at the end of each row,
         * creates a full copy of the array and the underlying data
         */
        void check_if_continuous();

        /**
         * Returns image size
         *
         * @return image_size
         */
        size_t* get_image_size();

        /**
         * Captures a frame from camera, if properly returns true
         *
         * @return true / false
         */
        bool read_frame();

        /**
         * Converts from RGB to G
         */
        void process_image();

        /**
         * Encodes image with and prepares to send through sockets
         */
        void encode_image();


    };
}

#endif //VIDEOSTREAMING_CAMERA_H