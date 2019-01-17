#include "network.h"

Network::Network()
{
    this ->serverIP = "127.0.0.1";
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
    char* charIp = new char[this ->serverIP.length() + 1];
    strcpy(charIp, this ->serverIP.c_str());

    this ->server.sin_family = PF_INET;
    this ->server.sin_addr.s_addr = inet_addr(charIp);
    this ->server.sin_port = htons(this ->serverPort);

    delete [] charIp;
}

void Network::connectToServer()
{
    int resultOfConnection;
    auto conversionToSockaddr = reinterpret_cast<sockaddr*>(&(this ->server));

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
         std::cout << "Failed when receiving data!" << std::endl;
}

void Network::closeConnection()
{
    close(this ->sockSystemCall);
}

uint16_t Network::getPort()
{
    return (this ->serverPort);
}

void Network::setPort(uint16_t newPort)
{
    this ->serverPort = newPort;
}

std::string Network::getServerIp()
{
    return (this ->serverIP);
}

void Network::setServerIp(std::string newIp)
{
    this ->serverIP = std::move(newIp);
}