/*

Written by Mateusz Rzeczyca.
Student - AGH University of Science and Technology
info@mateuszrzeczyca.pl
20.01.2019

*/

#ifndef VIDEOSTREAM_MENU_H
#define VIDEOSTREAM_MENU_H

#include "Network.h"
#include "Camera.h"

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
