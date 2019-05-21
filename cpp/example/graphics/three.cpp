#include "opencv2/opencv.hpp"

void to_gray_m3(const cv::Mat &input, cv::Mat &output)
{
    unsigned char* data_in = (unsigned char*)(input.data);
    unsigned char* data_out = (unsigned char*)(output.data);

    int index = 0;
    for (int row = 0; row < input.rows; ++row)
        for (int col = 0; col < input.cols * input.channels(); col += input.channels())
        {
            data_out[index]= 0.11*data_in[row*input.step+col]+
                             0.59*data_in[row*input.step+col+1]+
                             0.3*data_in[row*input.step+col+2];
            index++;
        }
}

int main()
{
    cv::Mat frame;
    cv::Mat output;
    to_gray_m3(frame, output);
    return 0;
}