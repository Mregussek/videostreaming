/*

Written by Mateusz Rzeczyca.
Student - AGH University of Science and Technology
info@mateuszrzeczyca.pl
20.01.2019

*/

#ifndef VIDEOSTREAM_NETWORK_H
#define VIDEOSTREAM_NETWORK_H

#include <iostream>
#include <unistd.h>
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
    bool sendData(cv::Mat, size_t);
    void closeConnection();

    // for the menu class
    uint16_t getPort();
    void setPort(uint16_t);

};


#endif //VIDEOSTREAM_NETWORK_H
