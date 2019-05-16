#include "opencv2/opencv.hpp"

int main(int, char**)
{
    cv::VideoCapture cap(0);
    if(! cap.isOpened() )
        return -1;

    cv::Mat edges;
    cv::Size size;
    size_t sizeInBytes_1;
    size_t sizeInBytes_2;
    cv::namedWindow("edges",1);
    
    for(;;)
    {
        cv::Mat frame;
        cap >> frame;

        size = frame.size();
        sizeInBytes_1 = frame.total() * frame.elemSize();
        sizeInBytes_2 = frame.step[0] * frame.rows;

        std::cout << size;
        std::cout << " height: " << size.height << " width: " << size.width << "\n";
        std::cout << frame.size();
        std::cout << " height: " << frame.rows << " width: " << frame.cols << "\n";
        std::cout << "bytes_1: " << sizeInBytes_1 << " bytes_2: " << sizeInBytes_2 << "\n";
        std::cout << "---------------------------------------------------------\n";

        cv::cvtColor(frame, edges, cv::COLOR_BGR2GRAY);

        cv::imshow("edges", edges);

        if(cv::waitKey(30) >= 0)
            break;
    }

    return 0;
}