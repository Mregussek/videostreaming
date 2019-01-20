#ifndef VIDEOSTREAM_MENU_H
#define VIDEOSTREAM_MENU_H

#include "Network.h"
#include "Camera.h"
#include <unistd.h>


class Menu : public Camera, public Network
{
private:
    bool resultOfReadingFrame;
    bool resOfSending;
public:
    Menu();
    void menu();
    void startStreaming();
    void usage();
    void configure();
    void clearScreen();

    void changePort();
};

#endif //VIDEOSTREAM_MENU_H
