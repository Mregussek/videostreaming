#ifndef VIDEOSTREAM_MENU_H
#define VIDEOSTREAM_MENU_H

#include "Network.h"
#include "Camera.h"

class Menu
{
public:
    void menu();
    void startStreaming();
    void usage();
    void configure();
    void clearScreen();

    void changePort();
};


#endif //VIDEOSTREAM_MENU_H
