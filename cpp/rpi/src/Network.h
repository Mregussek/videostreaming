#ifndef VIDEOSTREAM_NETWORK_H
#define VIDEOSTREAM_NETWORK_H

#include <iostream>
#include <arpa/inet.h>
#include <opencv2/opencv.hpp>

class Network {
    int serverSocket;
    int clientSocket;
    uint16_t port;
    sockaddr_in server;
    sockaddr_in client;
    socklen_t addressLength;

public:
    Network();
    // for networking
    void defServerSocket();
    void defSockaddr(uint16_t);
    void createServerAndListen();
    void acceptFirstConnection();
    void sendData(cv::Mat, size_t);

    // for the menu class
    uint16_t getPort();
    void setPort(uint16_t);

};


#endif //VIDEOSTREAM_NETWORK_H
