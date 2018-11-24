//
// Created by mateusz on 22.11.18.
//

#include <opencv2/opencv.hpp>
#include <sys/socket.h>
#include <iostream>
#include "src/network.h"
#include "src/camera.h"

void menu();
void streaming();
void watching();

int main()
{
    menu();
}

void menu()
{
    begin:
    system("clear");

    std::cout << "1. Watch" << std::endl;
    std::cout << "2. Stream" << std::endl;
    std::cout << "3. Exit";
    std::cout << "Please type correct number!" << std::endl;
    std::cout << "Choice:";

    int choice;
    std::cin >> choice;

    switch(choice)
    {
        case 1:
            watching();
            break;
        case 2:
            streaming();
            break;
        default:
            goto begin;
    }
}

void streaming()
{
    std::unique_ptr<network> streamVideo =
            std::make_unique<network>(7123, "10.42.0.30", "tcp");

    streamVideo ->createSocket();
    streamVideo ->bindServer( streamVideo ->serverAddress );
    streamVideo ->listenForConnection();
    streamVideo ->acceptCall( streamVideo ->clientAddress );

    // now should start streaming

    std::unique_ptr<camera> sendVideo =
            std::make_unique<camera>();
    std::shared_ptr<cv::Mat> image =
            std::make_shared<cv::Mat>();

    sendVideo ->getImage(image);
    sendVideo ->cropImage(image);

    size_t imageSize = sendVideo ->getImageSize(image);
    streamVideo ->sendData(image ->data, imageSize);

    streamVideo ->closeConnection();
}

void watching()
{
    std::unique_ptr<network> watchVideo =
            std::make_unique<network>(7123, "10.42.0.30", "tcp");

    watchVideo ->createSocket();
    watchVideo ->connectServer( watchVideo ->serverAddress );

    // now we should be allowed to see stream

    std::unique_ptr<camera> stream =
            std::make_unique<camera>();

    while(true)
    {
        std::shared_ptr<cv::Mat> image = stream ->getImageToReceive();

        size_t imageSize = stream ->getImageSize( image );
        unsigned char socketData[imageSize];

        for(int i = 0; i < imageSize; i += *watchVideo ->receivedData)
            watchVideo ->receiveData(socketData + i, imageSize - i);

        int pointer = 0;

        for(int i = 0; i < ROWS; i++)
        {
            for(int j = 0; j < COLUMNS; j++)
            {
                image ->at<cv::Vec3b>(i, j) =
                        cv::Vec3b(socketData[pointer + 0], socketData[pointer + 1], socketData[pointer + 2]);

                pointer += 3;
            }
        }

        cv::namedWindow("VideoStream", cv::WINDOW_AUTOSIZE);
        cv::imshow("Server", *image);

        char key = static_cast<char>( cv::waitKey(30) );
        if(key == 27)
            break;
    }

    watchVideo ->closeConnection();
}
