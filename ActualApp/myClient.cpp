#include <sys/socket.h>
#include "opencv2/opencv.hpp"
#include <arpa/inet.h>
#include <net/if.h>
#include <unistd.h>
#include <string.h>
#include <cstdlib>

using namespace cv;

void run();
void * capture(void *);

// global object for getting data from camera
VideoCapture captureDevice(0);

int main()
{
    run();
}

void run()
{
    int socketSystemCall, acceptSystemCall, 
                bindSystemCall, portNumber;
    char buffer[256];
    pthread_t thread_id;
    struct sockaddr_in serverAddress, clientAddress;
    int serverAddSize;
    int clientAddSize;

    portNumber = 3305;

    sockSystemCall = socket(AF_INET, SOCK_DGRAM, 0);

    if(sockSystemCall < 0)
        exit(0);

    // sets all values in buffer to 0        
    serverAddSize = sizeof(serverAddress);
    clientAddSize = sizeof(clientAddress);
    bzero( (char *) &serverAddress, serverAddSize);

    // sin_family contains code for address family
    serverAddress.sin_family = AF_INET;
    // sin_addr.s_addr contains ip address
    serverAddress.sin_addr.S_addr = INADDR_ANY;
    // sin_port contains port number
    // maybe htons !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    serverAddress.sin_port = htonl(portNumber);

    // bind the server and check if it runs
    bindSystemCall = bind(socketSystemCall, 
                        (struct sockaddr *) &serverAddress, &clientAddSize);
    if(bindSystemCall < 0)
        exit(0);

    // listen for connections
    listen(sockSystemCall, 5);

    // accept first incoming and exit if there is an issue
    acceptSystemCall = accept(socketSystemCall, 
                                (struct sockaddr *) &clientAddress, &clientAddSize);
    
    if(acceptSystemCall < 0)
        exit(0);

    pthread_create( &thread_id, NULL, capture, &acceptSystemCall);s
}

void * capture(void * pointer)
{
    int serverFor = *(int *)pointer;
    int rows, columns;


    // now it will gain data from camera and send it to server 
    Mat image, grayImage;

    rows = 640;
    columns = 480;
    // CV_8UC1 because i will use utf-8
    image = Mat::zeros(rows, columns, CV_8UC1);
}
