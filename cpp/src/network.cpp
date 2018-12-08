//
// Created by Mateusz Rzeczyca.
// Library for networking
//

#include <sys/socket.h>
#include <sys/types.h>
#include <string>
#include "network.h"

network::network()
: network(7123, "127.0.0.1", "tcp")
{

}

network::network(uint16_t port, std::string ip, std::string protocol)
{
    portNumber = port;
    ipAddress = ip;
    protocolType = protocol;
    addressSize = sizeof(sockaddr_in);
}

void network::initializeSockaddr(sockaddr_in socketAddr, std::string ipAddress)
{
    socketAddr.sin_family = AF_INET;
    socketAddr.sin_addr.s_addr = inet_addr( ipAddress.c_str() );
    socketAddr.sin_port = htons(portNumber);
}

void network::createSocket()
{
    int protocolNumber = getProtocolNumber(protocolType);

    if(protocolNumber < 0)
        //throw("Badly chosen protocol!");
        exit(0);

    switch(protocolNumber)
    {
        case 1:
            sockSystemCall = socket(AF_INET, SOCK_STREAM, 0);
            break;
        case 2:
            sockSystemCall = socket(AF_INET, SOCK_DGRAM, 0);
            break;
        default:
            //throw ("Not expected protocol type!");
            exit(0);
    }

    if(sockSystemCall < 0)
        //throw("Cannot create socket object");
        exit(0);
}

int network::getProtocolNumber(std::string& protocolType) const
{
    if(protocolType == "tcp")
        return 1;
    else if (protocolType == "udp")
        return 2;
    else
        return -1;
}

int network::acceptCall(sockaddr_in clientObject)
{
    auto address = reinterpret_cast<sockaddr*>(&clientObject);
    auto size = reinterpret_cast<socklen_t*>(&addressSize);

    // accept(int, struct sockaddr *, socklen_t *)
    acceptSystemCall = accept(sockSystemCall, address, size);

    if(acceptSystemCall < 0)
        //throw("Cannot accept connection!");
        exit(0);
}

int network::bindServer(sockaddr_in serverObject)
{
    auto serverPointer = reinterpret_cast<sockaddr*>(&serverObject);
    // bind(int, struct sockaddr *, socklen_t)
    bindSystemCall = bind(sockSystemCall, serverPointer, addressSize);

    if(bindSystemCall < 0)
        //throw("Cannot bind the server!");
        exit(0);

}

int network::connectServer(sockaddr_in& serverObject)
{
    auto serverPointer = reinterpret_cast<sockaddr*>(&serverObject);

    // connect(int, struct sockaddr *, socklen_t)
    connectSystemCall = connect(sockSystemCall, serverPointer, addressSize);

    if(connectSystemCall < 0)
        //throw("Cannot connect to server!");
        exit(0);
}

void network::listenForConnection() const
{
    listen(sockSystemCall, DEVICES);
}

void network::closeConnection() const
{
    shutdown(sockSystemCall, SHUT_RDWR);
}

int network::sendData(unsigned char* data, size_t size)
{
    ssize_t transfer;
    // send(int, unsigned char *, size_t, int)
    transfer = send(connectSystemCall, data, size, 0);
    int result = (int) transfer;
    return result;

}

void network::receiveData(unsigned char* socketData, size_t size)
{
    // recv(int, unsigned char *, size_t, int)
    receivedData = recv(sockSystemCall, socketData, size, 0);

    if(receivedData < 0)
        //throw("Cannot receive data!");
        exit(0);
}