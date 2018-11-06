#include "opencv2/opencv.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

void run();

int main()
{
    run();

    return 0;
}

void run()
{
    int mainSocket, connectSocket, serverPort;
    struct sockaddr_in serverAddress;
    struct hostent getHostName;
    char hostName = "pi@raspberrypi";

    // may work :D
    getHostName = gethostbyname(hostName);

    // change to SOCK_DGRAM for UDP
    mainSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(mainSocket < 0)
        exit(0);

    serverPort = 3305;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(getHostName);
    serverAddress.sin_port = htons( (uint16_t) serverPort);

    connectSocket = connect(mainSocket, (struct sockaddr *) &serverAddress,
                                            sizeof(serverAddress) );

    if(connectSocket < 0)
        exit(0);

    // now device is connected to RPi
    // time to begin streaming video

    cv::namedWindow("VideoStream", 1);

    cv::Mat image;
    uchar* iptr = image.data();
    int rows;
    int columns;

    rows = 640;
    columns = 480;

    image = cv::Mat::zeros(rows, columns, CV_8UC1);

    size_t imageSize = image.total() * image.elemSize();
    ssize_t bytes = 0;

    if(!image.isContinuous())
        image = image.clone();

    while(true)
    {
        bytes = recv(mainSocket, iptr, imageSize, MSG_WAITALL);

        if(bytes == -1)
                exit(0);

        cv::imshow("cv", image);
    }

    close(mainSocket);
}