//
// Created by Mateusz Rzeczyca.
// Library for networking made with socket.h and inet.h
// Tested only with Raspberry Pi to stream video using TCP and UDP protocols
//

#include <sys/socket.h>
#include <sys/types.h>
#include <memory>
#include "networkPointers.h"

networkPointers::networkPointers()
        : networkPointers(3305, "127.0.0.1", "tcp")
{
    addressSize = std::make_unique<socklen_t>( sizeof(sockaddr_in) );

}

networkPointers::networkPointers(uint16_t port, std::string ipAddress, std::string protocol)
        : portNumber( std::make_unique<uint16_t >(port) ),
          ipAddress( std::make_unique<std::string>(ipAddress) ),
          protocolType( std::make_unique<std::string>(protocol) ),
          addressSize( std::make_unique<socklen_t>( sizeof(sockaddr_in) ) )
{

}

void networkPointers::initializeSockaddr(std::shared_ptr<sockaddr_in> sockaddr, std::string ipAddress)
{
    sockaddr ->sin_family = AF_INET;
    sockaddr ->sin_addr.s_addr = inet_addr( ipAddress.c_str() );
    sockaddr ->sin_port = htons(*portNumber);
}


void networkPointers::createSocket()
{
    int protocolNumber = getProtocolNumber(*protocolType);

    if(protocolNumber < 0)
        throw("Badly chosen protocol!");

    switch(protocolNumber)
    {
        case 1:
            this ->sockSystemCall =
                    std::make_unique<int>( socket(AF_INET, SOCK_STREAM, 0) );
            break;
        case 2:
            this ->sockSystemCall =
                    std::make_unique<int>( socket(AF_INET, SOCK_DGRAM, 0) );
            break;
        default:
            throw ("Not expected protocol type!");
    }

    if(*sockSystemCall < 0)
        throw("Cannot create socket object");
}

int networkPointers::getProtocolNumber(std::string& protocolType) const
{
    if(protocolType == "tcp")
        return 1;
    else if (protocolType == "udp")
        return 2;
    else
        return -1;
}

int networkPointers::acceptCall(std::shared_ptr<sockaddr_in>& clientObject)
{
    auto address =
            reinterpret_cast<sockaddr*>( clientObject.get() );
    auto size =
            reinterpret_cast<socklen_t*>( addressSize.get() );

    this ->acceptSystemCall =
            std::make_unique<int>( accept(*sockSystemCall, address, size) );

    delete address;
    delete size;

    if(*acceptSystemCall < 0)
        throw("Cannot accept connection!");
}

int networkPointers::bindServer(std::shared_ptr<sockaddr_in>& serverObject)
{
    auto address =
            reinterpret_cast<sockaddr*>( serverObject.get() );

    this ->bindSystemCall =
            std::make_unique<int>( bind(*sockSystemCall, address , *addressSize) );

    delete address;

    if(*bindSystemCall < 0)
        throw("Cannot bind the server!");

}

int networkPointers::connectServer(std::shared_ptr<sockaddr_in>& serverObject)
{
    auto address =
            reinterpret_cast<sockaddr*>( serverObject.get() );

    this ->connectSystemCall =
            std::make_unique<int>( connect(*sockSystemCall, address, *addressSize) );

    delete address;

    if(*connectSystemCall < 0)
        throw("Cannot connect to server!");
}

void networkPointers::listenForConnection() const
{
    listen(*sockSystemCall, DEVICES);
}

void networkPointers::listenForConnection(int numberOfDevices) const
{
    listen(*sockSystemCall, numberOfDevices);
}

void networkPointers::closeConnection() const
{
    shutdown(*sockSystemCall, SHUT_RDWR);
}

void networkPointers::sendData(unsigned char* data, size_t size)
{
    sentData =
            std::make_unique<int>( send(*sockSystemCall, data, size, 0) );

    if(*sentData < 0)
        throw("Cannot send data!");
}

void networkPointers::receiveData(unsigned char* socketData, size_t size)
{
    receivedData =
            std::make_shared<ssize_t>( recv(*sockSystemCall, socketData, size, 0) );

    if(*receivedData < 0)
        throw("Cannot receive data!");
}


