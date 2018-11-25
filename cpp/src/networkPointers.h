//
// Created by mateusz on 25.11.18.
//

#ifndef VIDEOSTREAM_NETWORKPOINTERS_H
#define VIDEOSTREAM_NETWORKPOINTERS_H


#include <sys/socket.h>
#include <arpa/inet.h>
#include <memory>

#define DEVICES 3

class networkPointers {
private:
    std::unique_ptr<int> sockSystemCall;
    std::unique_ptr<int> acceptSystemCall;
    std::unique_ptr<int> bindSystemCall;
    std::unique_ptr<int> connectSystemCall;
    std::unique_ptr<int> sentData;
    std::unique_ptr<std::string> protocolType;
    std::unique_ptr<uint16_t > portNumber;
public:
    std::shared_ptr<sockaddr_in> serverAddress;
    std::shared_ptr<sockaddr_in> clientAddress;
private:
    std::unique_ptr<socklen_t> addressSize;
    std::unique_ptr<std::string> ipAddress;
public:
    std::shared_ptr<ssize_t> receivedData;


    networkPointers();
    networkPointers(uint16_t, std::string, std::string);

    void createSocket();
    // use clientAddress
    int acceptCall(std::shared_ptr<sockaddr_in>&);
    // for those use serverAddress
    int bindServer(std::shared_ptr<sockaddr_in>&);
    int connectServer(std::shared_ptr<sockaddr_in>&);
    void listenForConnection() const;
    // this int means the amount of devices
    void listenForConnection(int) const;
    void closeConnection() const;
    void sendData(unsigned char*, size_t);
    void receiveData(unsigned char*, size_t);

private:
    void initializeSockaddr(std::shared_ptr<struct sockaddr_in>, std::string);
    int getProtocolNumber(std::string&) const;
};



#endif //VIDEOSTREAM_NETWORKPOINTERS_H
