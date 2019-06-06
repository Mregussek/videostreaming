//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   rzeczyca@student.agh.edu.pl
//   30.03.2019

#ifndef VIDEOSTREAMING_DISPLAYER_H
#define VIDEOSTREAMING_DISPLAYER_H

#include <opencv2/opencv.hpp>

namespace mrz
{
    /**
     * Implements class for displaying mats
     */
    class Displayer
    {
    public:
        int* key;
    private:
        cv::Mat* raw_data;
        cv::Mat* image;
        size_t* image_size;

    public:
        /**
         * Initializes elements for TCP-based app
         */
        Displayer();

        /**
         * Initializes elements for UDP-based app
         *
         * @param pack stores how many packets socket got
         * @param image_metadata stored in uchar* (like image.data, where image is cv::Mat)
         */
        Displayer(int pack, char* image_metadata);

        /**
         * Deallocates memory
         */
        ~Displayer();

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
         * Decodes image in case of correct displaying it, Mat is received from socket
         */
        void decode_image();

        /**
         * Waits for key event and returns clicked k
         *
         * @return key
         */
        int wait();

        /**
         * Returns image metadata, the one which is displayed
         *
         * @param image.data
         */
        uchar* get_metadata();

        /**
         * Displays image with title
         *
         * @param protocol is added to "VideoStreaming" title
         */
        void show_image(const std::string protocol);
    };
}

#endif //VIDEOSTREAMING_DISPLAYER_H