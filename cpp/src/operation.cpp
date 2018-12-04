//
// Created by mateusz on 28.11.18.
//

#include <opencv2/opencv.hpp>
#include <sys/socket.h>
#include "camera.h"
#include "network.h"
#include "file.h"
#include "operation.h"

void operation::streaming()
{
    std::string address = "127.0.0.1";
    std::string protocol = "tcp";
    auto server = new network(7123, address, protocol);

    server ->createSocket();
    server ->initializeSockaddr(server ->serverAddress, server ->ipAddress);
    server ->bindServer(server ->serverAddress);
    server ->listenForConnection();

    std::cout << "Waiting for connections" << std::endl;

    server ->acceptCall(server ->clientAddress);
    // when device is connected start streaming

    auto cam = new camera();
    cv::Mat image;
    int result;
    std::string data;

    while(true)
    {
        std::cout << "Capturing" << std::endl;
        image = cam ->captureImage();
        image = cam ->cropImage(image);
        data = cam ->encodeData(image);

        std::cout << "Sending" << std::endl;
        result = server ->sendData((unsigned char*) data.data(), data.size());

        if(result < 0)
            break;
    }

    server ->closeConnection();
    exit(0);
}

void operation::watching()
{

}