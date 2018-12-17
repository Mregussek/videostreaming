//
// Created by mateusz on 27.11.18.
//

#ifndef VIDEOSTREAM_MAIN_H
#define VIDEOSTREAM_MAIN_H

#include <opencv2/opencv.hpp>
#include <sys/socket.h>
#include "Camera.h"
#include "Network.h"

class Network;
class Camera;
class Operation;

class Operation
{
public:
    Operation() {};

    void streaming();
    void watching();
    void menu();
};

#endif //VIDEOSTREAM_MAIN_H
