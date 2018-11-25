//
// Created by Mateusz Rzeczyca.
// Library for networking made with socket.h and inet.h
// Tested only with Raspberry Pi to stream video using TCP and UDP protocols
//

#include <sys/socket.h>
#include <sys/types.h>
#include <memory>
#include "network.h"

network::network()
: portNumber( 3305 ),
    ipAddress( "127.0.0.1" ),
        protocolType( "tcp" ),
            addressSize( sizeof(sockaddr_in) )
{

}

network::network(uint16_t port, std::string ipAddress, std::string protocol)
: portNumber( port ),
    ipAddress( ipAddress ),
        protocolType( protocol ),
                addressSize( sizeof(sockaddr_in) )
{

}

void network::initializeSockaddr(sockaddr_in& sockaddr, std::string& ipAddress)
{
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = inet_addr( ipAddress.c_str() );
    sockaddr.sin_port = htons(this ->portNumber);
}


void network::createSocket()
{
    int protocolNumber = getProtocolNumber(protocolType);

    if(protocolNumber < 0)
        throw("Badly chosen protocol!");

    switch(protocolNumber)
    {
        case 1:
            this ->sockSystemCall =
                    socket(AF_INET, SOCK_STREAM, 0);
            break;
        case 2:
            this ->sockSystemCall =
                    socket(AF_INET, SOCK_DGRAM, 0);
            break;
        default:
            throw ("Not expected protocol type!");
    }

    if(sockSystemCall < 0)
        throw("Cannot create socket object");
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

int network::acceptCall(sockaddr_in& clientObject)
{
    auto address = (sockaddr*) &clientObject;
    auto size = &(this ->addressSize);

    this ->acceptSystemCall =
            accept(this ->sockSystemCall, address, size);

    delete address;

    if(acceptSystemCall < 0)
        throw("Cannot accept connection!");
}

int network::bindServer(sockaddr_in& serverObject)
{
    auto serverPointer = (sockaddr*) &serverObject;

    this ->bindSystemCall =
            bind(this ->sockSystemCall, serverPointer , addressSize);

    delete serverPointer;

    if(bindSystemCall < 0)
        throw("Cannot bind the server!");

}

int network::connectServer(sockaddr_in& serverObject)
{
    auto serverPointer = (sockaddr*) &serverObject;

    this ->connectSystemCall =
            connect(this ->sockSystemCall, serverPointer, addressSize);

    delete serverPointer;

    if(connectSystemCall < 0)
        throw("Cannot connect to server!");
}

void network::listenForConnection() const
{
    listen(sockSystemCall, DEVICES);
}

void network::listenForConnection(int numberOfDevices) const
{
    listen(sockSystemCall, numberOfDevices);
}

void network::closeConnection() const
{
    shutdown(sockSystemCall, SHUT_RDWR);
}

void network::sendData(unsigned char* data, size_t size)
{
    sentData =
            send(sockSystemCall, data, size, 0);

    if(sentData < 0)
        throw("Cannot send data!");
}

void network::receiveData(unsigned char* socketData, size_t size)
{
    receivedData =
            recv(sockSystemCall, socketData, size, 0);

    if(receivedData < 0)
        throw("Cannot receive data!");
}


