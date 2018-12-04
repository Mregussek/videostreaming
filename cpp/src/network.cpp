//
// Created by Mateusz Rzeczyca.
// Library for networking
//

#include <sys/socket.h>
#include <sys/types.h>
#include <string>
#include "network.h"

network::network()
{
    portNumber = new uint16_t(3305);
    ipAddress = new std::string("127.0.0.1");
    protocolType = new std::string("tcp");
    addressSize = new socklen_t( sizeof(sockaddr_in) );

    sockSystemCall = new int();
    bindSystemCall = new int();
    connectSystemCall = new int();
    acceptSystemCall = new int();
    receivedData = new ssize_t();
    serverAddress = new sockaddr_in();
    clientAddress = new sockaddr_in();
}

network::network(uint16_t port, std::string& ip, std::string& protocol)
{
    portNumber = new uint16_t( port );
    ipAddress = new std::string( ip );
    protocolType = new std::string( protocol );
    addressSize = new socklen_t( sizeof(sockaddr_in) );

    sockSystemCall = new int();
    bindSystemCall = new int();
    connectSystemCall = new int();
    acceptSystemCall = new int();
    receivedData = new ssize_t();
    serverAddress = new sockaddr_in();
    clientAddress = new sockaddr_in();
}

network::~network()
{
    delete portNumber;
    delete ipAddress;
    delete protocolType;
    delete addressSize;
    delete sockSystemCall;
    delete bindSystemCall;
    delete connectSystemCall;
    delete acceptSystemCall;
    delete receivedData;
    delete serverAddress;
    delete clientAddress;
}

void network::initializeSockaddr(sockaddr_in& sockaddr, std::string& ipAddress)
{
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = inet_addr( ipAddress.c_str() );
    sockaddr.sin_port = htons(*portNumber);
}

void network::createSocket()
{
    int protocolNumber = getProtocolNumber(*protocolType);

    if(protocolNumber < 0)
        //throw("Badly chosen protocol!");
        exit(0);

    switch(protocolNumber)
    {
        case 1:
            *sockSystemCall = socket(AF_INET, SOCK_STREAM, 0);
            break;
        case 2:
            *sockSystemCall = socket(AF_INET, SOCK_DGRAM, 0);
            break;
        default:
            //throw ("Not expected protocol type!");
            exit(0);
    }

    if(*sockSystemCall < 0)
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

int network::acceptCall(sockaddr_in* clientObject)
{
    auto address = reinterpret_cast<sockaddr*>(clientObject);

    // accept(int, struct sockaddr *, socklen_t *)
    *acceptSystemCall = accept(*sockSystemCall, address, addressSize);

    //delete address;

    if(*acceptSystemCall < 0)
        //throw("Cannot accept connection!");
        exit(0);
}

int network::bindServer(sockaddr_in* serverObject)
{
    auto serverPointer = reinterpret_cast<sockaddr*>(serverObject);

    // bind(int, struct sockaddr *, socklen_t)
    this ->bindSystemCall = bind(*sockSystemCall, serverPointer , *addressSize);

    //delete serverPointer;
    if(*bindSystemCall < 0)
        //throw("Cannot bind the server!");
        exit(0);

}

int network::connectServer(sockaddr_in& serverObject)
{
    auto serverPointer = (sockaddr*) &serverObject;

    // connect(int, struct sockaddr *, socklen_t)
    *connectSystemCall = connect(*sockSystemCall, serverPointer, *addressSize);

    //delete serverPointer;

    if(*connectSystemCall < 0)
        //throw("Cannot connect to server!");
        exit(0);
}

void network::listenForConnection() const
{
    listen(*sockSystemCall, DEVICES);
}

void network::listenForConnection(int numberOfDevices) const
{
    listen(*sockSystemCall, numberOfDevices);
}

void network::closeConnection() const
{
    shutdown(*sockSystemCall, SHUT_RDWR);
}

int network::sendData(unsigned char* data, size_t size)
{
    ssize_t transfer;
    // send(int, unsigned char *, size_t, int)
    transfer = send(*connectSystemCall, data, size, 0);
    int result = (int) transfer;
    return result;

}

void network::receiveData(unsigned char* socketData, size_t size)
{
    // recv(int, unsigned char *, size_t, int)
    *receivedData = recv(*sockSystemCall, socketData, size, 0);

    if(*receivedData < 0)
        //throw("Cannot receive data!");
        exit(0);
}