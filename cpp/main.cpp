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
    std::cout << "3. Exit" << std::endl;
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
        case 3:
            exit(0);
        default:
            goto begin;
    }
}

void streaming()
{
    std::unique_ptr<network> streamVideo = std::make_unique<network>(3305, "127.0.0.1", "tcp");

    streamVideo ->createSocket();
    streamVideo ->initializeSockaddr(streamVideo ->serverAddress, streamVideo ->ipAddress);
    streamVideo ->bindServer( streamVideo ->serverAddress );
    streamVideo ->listenForConnection();
    streamVideo ->acceptCall( streamVideo ->clientAddress );

    // now should start streaming

    std::unique_ptr<camera> sendVideo = std::make_unique<camera>();
    cv::Mat image;
    bool checkImage;

    while(true)
    {
        image = sendVideo ->captureImage();
        checkImage = sendVideo->checkImage(image);

        if(!checkImage)
            break;

        sendVideo ->cropImage(image);

        size_t imageSize = sendVideo ->getImageSize(image);
        streamVideo ->sendData(image, imageSize);
    }

    streamVideo ->closeConnection();
}

void watching()
{
    std::unique_ptr<network> watchVideo = std::make_unique<network>(3305, "127.0.0.1", "tcp");

    watchVideo ->createSocket();
    watchVideo ->initializeSockaddr(watchVideo ->serverAddress, watchVideo ->ipAddress);
    watchVideo ->connectServer( watchVideo ->serverAddress );

    std::unique_ptr<camera> stream = std::make_unique<camera>();

    while(true)
    {
        cv::Mat image = stream ->getImageToReceive();

        size_t imageSize = stream ->getImageSize( image );
        unsigned char socketData[imageSize];

        for(int i = 0; i < imageSize; i += watchVideo ->receivedData)
            watchVideo ->receiveData(socketData + i, imageSize - i);

        int pointer = 0;

        for(int i = 0; i < ROWS; i++)
        {
            for(int j = 0; j < COLUMNS; j++)
            {
                image.at<cv::Vec3b>(i, j) = cv::Vec3b(socketData[pointer + 0], socketData[pointer + 1], socketData[pointer + 2]);

                pointer += 3;
            }
        }

        cv::namedWindow("VideoStream", cv::WINDOW_AUTOSIZE);
        cv::imshow("Server", image);

        char key = static_cast<char>( cv::waitKey(30) );
        if(key == 27)
            break;
    }

    watchVideo ->closeConnection();
}
