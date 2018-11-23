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
: network(3305, "127.0.0.1", "tcp")
{
    addressSize = std::make_unique<socklen_t>( sizeof(sockaddr_in) );

}

network::network(uint16_t port, std::string ipAddress, std::string protocol)
: portNumber( std::make_unique<uint16_t >(port) ),
    ipAddress( std::make_unique<std::string>(ipAddress) ),
        protocolType( std::make_unique<std::string>(protocol) ),
                addressSize( std::make_unique<socklen_t>( sizeof(sockaddr_in) ) )
{

}

void network::initializeSockaddr(std::shared_ptr<sockaddr_in> sockaddr, std::string ipAddress)
{
    sockaddr ->sin_family = AF_INET;
    sockaddr ->sin_addr.s_addr = inet_addr( ipAddress.c_str() );
    sockaddr ->sin_port = htons(*portNumber);
}


void network::createSocket()
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

int network::getProtocolNumber(std::string& protocolType)
{
    if(protocolType == "tcp")
        return 1;
    else if (protocolType == "udp")
        return 2;
    else
        return -1;
}

int network::acceptCall(std::shared_ptr<sockaddr_in>& clientObject)
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

int network::bindServer(std::shared_ptr<sockaddr_in>& serverObject)
{
    auto address =
            reinterpret_cast<sockaddr*>( serverObject.get() );

    this ->bindSystemCall =
            std::make_unique<int>( bind(*sockSystemCall, address , *addressSize) );

    delete address;

    if(*bindSystemCall < 0)
        throw("Cannot bind the server!");

}

int network::connectServer(std::shared_ptr<sockaddr_in>& serverObject)
{
    auto address =
            reinterpret_cast<sockaddr*>( serverObject.get() );

    this ->connectSystemCall =
            std::make_unique<int>( connect(*sockSystemCall, address, *addressSize) );

    delete address;

    if(*connectSystemCall < 0)
        throw("Cannot connect to server!");
}

void network::listenForConnection()
{
    listen(*sockSystemCall, DEVICES);
}

void network::listenForConnection(int numberOfDevices)
{
    listen(*sockSystemCall, numberOfDevices);
}

void network::closeConnection()
{
    shutdown(*sockSystemCall, SHUT_RDWR);
}


