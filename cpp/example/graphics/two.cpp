#include "opencv2/opencv.hpp"

void to_gray_m2(const cv::Mat &input, cv::Mat &output)
{
    unsigned char* data_in = (unsigned char*)(input.data);
    unsigned char* data_out = (unsigned char*)(output.data);

    int index = 0;
    int byte_size = input.channels() * input.rows * input.cols;
    while(index != byte_size)
    {
        data_out[index / input.channels()] = unsigned(
            0.11 * data_in[index] + 0.59 * data_in[index + 1] + 0.3 * data_in[index + 2]
            );

        index += 3;
    }
}

int main()
{
    cv::Mat frame;
    cv::Mat output;
    to_gray_m2(frame, output);
    return 0;
}