#include "opencv2/opencv.hpp"

void to_gray_m1(const cv::Mat &input, cv::Mat &output)
{
  
    unsigned char *data_out = (unsigned char*)(output.data);
    int ind = 0;
    auto end = input.end<cv::Vec3b>();
    cv::MatConstIterator_<cv::Vec3b> it = input.begin<cv::Vec3b>();
    for (; it != end; ++it)
    {
        const unsigned char& r = (*it)[2];
        const unsigned char& g = (*it)[1];
        const unsigned char& b = (*it)[0];
        data_out[ind] = 0.3 * r + 0.59 * g + 0.11 * b;
        ind++;
    }
}

int main()
{
    cv::Mat frame;
    cv::Mat output;
    to_gray_m1(frame, output);
    return 0;
}