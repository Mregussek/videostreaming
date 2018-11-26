//
// Created by Mateusz Rzeczyca.
// Library for networking made with socket.h and inet.h
// Tested only with Raspberry Pi to stream video using TCP and UDP protocols
//
// For creating a socket use one of the constructors:
// networkPointers() which is the default one with port 3305, ip address 127.0.0.1 and tcp protocol
// networkPointers(uint16_t, std::string, std::string) for port number, ip address and protocol type

#ifndef VIDEOSTREAM_NETWORK_H
#define VIDEOSTREAM_NETWORK_H

#include <opencv2/opencv.hpp>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <memory>

#define DEVICES 3

class network {
private:
    int sockSystemCall;
    int acceptSystemCall;
    int bindSystemCall;
    int connectSystemCall;
    ssize_t sentData;
    std::string protocolType;
    uint16_t portNumber;
public:
    sockaddr_in serverAddress;
    sockaddr_in clientAddress;
private:
    socklen_t addressSize;
public:
    std::string ipAddress;
    ssize_t receivedData;


    network();
    // change this std::move in the case of issue in initializer list
    network(uint16_t, std::string, std::string);

    void createSocket();
    // use clientAddress
    int acceptCall(sockaddr_in&);
    // for those use serverAddress
    int bindServer(sockaddr_in&);
    int connectServer(sockaddr_in&);
    void listenForConnection() const;
    // this int means the amount of devices
    void listenForConnection(int) const;
    void closeConnection() const;
    void sendData(cv::Mat&, size_t);
    void receiveData(unsigned char*, size_t);
    void initializeSockaddr(sockaddr_in&, std::string&);
private:
    int getProtocolNumber(std::string&) const;
};


#endif // VIDEOSTREAM_NETWORK_H
