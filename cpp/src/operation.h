//
// Created by mateusz on 27.11.18.
//

#ifndef VIDEOSTREAM_MAIN_H
#define VIDEOSTREAM_MAIN_H

#include <opencv2/opencv.hpp>
#include <sys/socket.h>
#include "camera.h"
#include "network.h"
#include "file.h"

class file;
class network;
class camera;
class operation;

class operation
{
public:
    operation() {};

    void streaming();
    void watching();
};

#endif //VIDEOSTREAM_MAIN_H