#include "opencv2/opencv.hpp"


int main()
{
    cv::Mat frame;
    cv::Mat output;
    cv::cvtColor(frame, output, cv::COLOR_BGR2GRAY);
    return 0;
}