#include "Network.h"

Network::Network()
{
    this ->port = 3305;
    this ->addressLength = sizeof(sockaddr_in);
}

void Network::defServerSocket()
{
    this ->serverSocket = socket(AF_INET , SOCK_STREAM , 0);

    if (this ->serverSocket == -1)
    {
        perror("Creating socket failed!");
    }
}

void Network::defSockaddr(uint16_t anyPort)
{
    this ->server.sin_family = AF_INET;
    this ->server.sin_addr.s_addr = INADDR_ANY;
    this ->server.sin_port = htons(anyPort);
}

void Network::createServerAndListen()
{
    auto conversionToSockaddr = (sockaddr*) &(this ->server);

    int resultOfBind = bind(this ->serverSocket,
                    conversionToSockaddr, this ->addressLength);

    if(resultOfBind < 0)
    {
        perror("Cannot bind socket!");
        exit(1);
    }

    listen(this ->serverSocket, 1);
    std::cout <<  "Waiting for connections...\n" <<
    "Server Address: " << inet_ntoa(this ->server.sin_addr) <<" Server Port:" << this ->port << std::endl;
}

void Network::acceptFirstConnection()
{
    auto conversionToSockaddr = (sockaddr*) &(this ->client);
    auto conversionToPointer = &(this ->addressLength);

    this ->clientSocket = accept(this ->serverSocket,
                        conversionToSockaddr, conversionToPointer);

    if(this ->clientSocket < 0)
    {
        perror("Accepting request failed!");
        exit(1);
    }

    std::cout << "Connection accepted" << std::endl;
}

void Network::sendData(cv::Mat image, size_t size)
{
    ssize_t resultOfSend = send(this ->clientSocket, image.data, size, 0);

    if (resultOfSend < 0)
    {
        std::cerr << "bytes = " << resultOfSend << std::endl;
    }
}

uint16_t Network::getPort()
{
    return this ->port;
}

void Network::setPort(uint16_t newPort)
{
    this ->port = newPort;
}