#ifndef VIDEOSTREAM_NETWORK_H
#define VIDEOSTREAM_NETWORK_H

#include <opencv2/opencv.hpp>
#include <opencv2/opencv.hpp>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

class Network {
    int sockSystemCall;
    char* serverIP;
    uint16_t serverPort;
    sockaddr_in server;
    socklen_t addressLength;
    ssize_t receivedBytes;

public:
    Network();
    void defSocket();
    void defSockaddr();
    void connectToServer();
    void receiveData(uchar*, size_t);
    void closeConnection();
};

#endif //VIDEOSTREAM_NETWORK_H
