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
    std::string serverIP;
    uint16_t serverPort;
    sockaddr_in server;
    socklen_t addressLength;
    ssize_t receivedBytes;

public:
    // for networking
    Network();
    void defSocket();
    void defSockaddr();
    void connectToServer();
    void receiveData(uchar*, size_t);
    void closeConnection();

    // for menu
    uint16_t getPort();
    void setPort(uint16_t);
    std::string getServerIp();
    void setServerIp(std::string);
};

#endif //VIDEOSTREAM_NETWORK_H
