//
// Created by mateusz on 22.11.18.
//

#ifndef CLIENTRPI_NETWORK_H
#define CLIENTRPI_NETWORK_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <memory>

#define DEVICES 3

class network {
public:
    network();
    explicit network(uint16_t);

    void createSocket(std::string);
    int acceptCall(std::shared_ptr<sockaddr_in>&);
    int bindServer(std::shared_ptr<sockaddr_in>&);
    int connectServer(std::shared_ptr<sockaddr_in>&);
    void listenForConnection();

private:
    std::unique_ptr<int> sockSystemCall;
    std::unique_ptr<int> acceptSystemCall;
    std::unique_ptr<int> bindSystemCall;
    std::unique_ptr<int> connectSystemCall;
    std::unique_ptr<uint16_t > portNumber;
    std::shared_ptr<sockaddr_in> serverAddress;
    std::shared_ptr<sockaddr_in> clientAddress;
    std::unique_ptr<socklen_t> addressSize;

    void initializeSockaddr(std::shared_ptr<struct sockaddr_in>, std::string);
    int getProtocolNumber(std::string&);
};


#endif //CLIENTRPI_NETWORK_H
