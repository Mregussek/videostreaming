//
// Created by mateusz on 28.11.18.
//

#include <opencv2/opencv.hpp>
#include <sys/socket.h>
#include "Camera.h"
#include "Network.h"
#include "file.h"
#include "operation.h"

void operation::streaming()
{
    uint16_t nPro = 7123;
    std::string address = "127.0.0.1";
    std::string sPro = "tcp";
    auto server = new Network(nPro, address, sPro);

    server ->createSocket();
    server ->initializeSockaddr(server ->serverAddress, server ->ipAddress);
    server ->bindServer(server ->serverAddress);
    server ->listenForConnection();

    std::cout << "Waiting for connections" << std::endl;

    server ->acceptCall(server ->clientAddress);
    // when device is connected start streaming

    auto cam = new Camera();
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
    uint16_t nPro = 7123;
    std::string address = "127.0.0.1";
    std::string sPro = "tcp";
    auto client = new Network(nPro, address, sPro);

    client ->createSocket();
    client ->initializeSockaddr(client ->serverAddress, client ->ipAddress);
    client ->connectServer(client ->serverAddress);

    std::cout << "Connected to server" << std::endl;

    auto stream = new Camera();
    cv::Mat image = *(stream ->imageToReceive);
    size_t imageSize = stream ->getImageSize( image );
    unsigned char* imageData = stream ->imageToReceive ->data;

    while(true)
    {
        client ->receiveData(imageData, imageSize);

        try {
            stream ->showImage();
        }
        catch(std::string s) {
            std::cout << s << std::endl;
            break;
        }
    }

    client ->closeConnection();
}
