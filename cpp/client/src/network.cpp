#include "network.h"

Network::Network()
{
    this ->serverIP = (char*)"127.0.0.1";
    this ->serverPort = 3305;
    this ->addressLength = sizeof(sockaddr_in);
    this ->receivedBytes = 0;
}

void Network::defSocket()
{
    this ->sockSystemCall = socket(PF_INET, SOCK_STREAM, 0);

    if(this ->sockSystemCall < 0)
    {
        std::cout << "There was an issue with creating a socket!" << std::endl;
        exit(1);
    }
}

void Network::defSockaddr()
{
    this ->server.sin_family = PF_INET;
    this ->server.sin_addr.s_addr = inet_addr(this ->serverIP);
    this ->server.sin_port = htons(this ->serverPort);
}

void Network::connectToServer()
{
    int resultOfConnection;
    auto conversionToSockaddr = (sockaddr*) &(this ->server);

    resultOfConnection = connect(this ->sockSystemCall,
            conversionToSockaddr, this ->addressLength);

    if(resultOfConnection < 0)
    {
        std::cout << "There was an issue with connecting to server!" << std::endl;
        exit(1);
    }
}

void Network::receiveData(uchar* metadata, size_t sizeOfImage)
{
    this ->receivedBytes = recv(this ->sockSystemCall, metadata,
                        sizeOfImage, MSG_WAITALL);

    if(receivedBytes == -1)
        std::cerr << "Failed in receiving data, received = " << this ->receivedBytes << std::endl;
}

void Network::closeConnection()
{
    close(this ->sockSystemCall);
}

uint16_t Network::getPort()
{
    return this ->serverPort;
}

void Network::setPort(uint16_t newPort)
{
    this ->serverPort = newPort;
}

char* Network::getServerIp()
{
    return this ->serverIP;
}

void Network::setServerIp(char* newIp)
{
    this ->serverIP = newIp;
}