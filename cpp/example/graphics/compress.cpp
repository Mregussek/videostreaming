#include "opencv2/opencv.hpp"

int main(int, char**)
{
    cv::VideoCapture cap(0);
    if(! cap.isOpened() )
        return -1;

    cv::Mat edges;
    cv::Mat frame;
    std::vector<uchar> encoded;
    int total_pack;
    
    for(;;)
    {
        cap >> frame;

        cv::resize(frame, edges, cv::Size(640, 480), 0, 0, cv::INTER_LINEAR);
        // For JPEG, it can be a quality ( CV_IMWRITE_JPEG_QUALITY ) from 0 to 100 (the higher is the better). Default value is 95.
        std::vector<int> compression;
        compression.push_back(cv::IMWRITE_JPEG_QUALITY);
        compression.push_back(80);
        cv::imencode(".jpg", edges, encoded, compression);

        //total_pack = 1 + (encoded.size() - 1) / 4096;
        total_pack = encoded.capacity() / 4096;
        std::cout << "encoded.size(): " << encoded.size() << " total_pack: " << total_pack
             << " encoded.capacity(): " << encoded.capacity() << "\n"

        if(cv::waitKey(30) >= 0)
            break;
    }

    return 0;
}