#include <sys/socket.h>
#include "opencv2/opencv.hpp"
#include <arpa/inet.h>
#include <net/if.h>
#include <unistd.h>
#include <string.h>
#include <cstdlib>
#include <pthread.h>

void run();
void * capture(void *);

int main()
{
    run();
}

void run()
{
    int sockSystemCall, acceptSystemCall,
                bindSystemCall, portNumber;
    pthread_t thread_id;
    struct sockaddr_in serverAddress, clientAddress;
    int clientAddSize;

    portNumber = 3305;

    sockSystemCall = socket(AF_INET, SOCK_DGRAM, 0);

    if(sockSystemCall < 0)
        exit(0);

    // sin_family contains code for address family
    serverAddress.sin_family = AF_INET;
    // sin_addr.s_addr contains ip address
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    // sin_port contains port number
    serverAddress.sin_port = htons((uint16_t )portNumber);

    // bind the server and check if it runs
    bindSystemCall = bind(sockSystemCall, (struct sockaddr *) &serverAddress,
            sizeof(serverAddress) );

    if(bindSystemCall < 0)
        exit(0);

    // listen for connections
    listen(sockSystemCall, 5);

    // accept first incoming and exit if there is an issue
    clientAddSize = sizeof(clientAddress);
    acceptSystemCall = accept(sockSystemCall, (struct sockaddr *) &clientAddress,
                                        (socklen_t *)&clientAddSize);
    
    if(acceptSystemCall < 0)
        exit(0);

    pthread_create( &thread_id, nullptr, capture, &acceptSystemCall);
}

void * capture(void * pointer)
{
    int serverFor = *(int *)pointer;
    int rows, columns;
    int numberOfDevice = 0;
    cv::VideoCapture captureDevice(numberOfDevice);

    // now it will gain data from camera and send it to server 
    cv::Mat image, grayImage;

    rows = 640;
    columns = 480;
    // CV_8UC1 because i will use utf-8
    image = cv::Mat::zeros(rows, columns, CV_8UC1);

    if( !image.isContinuous() )
        image = image.clone();

    size_t imgSize = image.total() * image.elemSize();
    ssize_t bytes;

    while( true )
    {
        captureDevice >> image;

        cvtColor(image, grayImage, CV_BGR2GRAY);

        bytes = send(serverFor, grayImage.data, imgSize, 0);

        if( bytes < 0 )
            break;
    }

}
