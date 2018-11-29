//
// Created by Mateusz Rzeczyca.
// Library for networking made with socket.h and inet.h
//
// For creating a socket use one of the constructors:
// networkPointers() which is the default one with port 3305, ip address 127.0.0.1 and tcp protocol
// networkPointers(uint16_t, std::string, std::string) for port number, ip address and protocol type
//

#ifndef VIDEOSTREAM_NETWORK_H
#define VIDEOSTREAM_NETWORK_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include "main.h"

#define DEVICES 3

class network {
private:
    int sockSystemCall; // default socket for calling
    int acceptSystemCall; // socket for accepting call
    int bindSystemCall; // socket for binding the server
    int connectSystemCall; // socket for ability to connect to the server
    ssize_t sentData; // as the name says
    std::string protocolType; // as the name says
    uint16_t portNumber; // as the name says
public:
    sockaddr_in serverAddress; // object for server
    sockaddr_in clientAddress; // object for client
private:
    socklen_t addressSize;
public:
    std::string ipAddress; // as the name says example: '192.168.10.10"
    ssize_t receivedData; // as the name says

    network();
    network(uint16_t, std::string, std::string);

    void createSocket();
    void initializeSockaddr(sockaddr_in&, std::string&);
    // use clientAddress
    int acceptCall(sockaddr_in&);
    // for those use serverAddress
    int bindServer(sockaddr_in&);
    int connectServer(sockaddr_in&);
    void listenForConnection() const;
    void listenForConnection(int) const; // this int means the amount of devices
    void closeConnection() const;
    int sendData(unsigned char*, size_t);
    void receiveData(unsigned char*, size_t);
private:
    int getProtocolNumber(std::string&) const;
};


#endif // VIDEOSTREAM_NETWORK_H
