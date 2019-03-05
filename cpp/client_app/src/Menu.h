/*

Written by Mateusz Rzeczyca.
Student - AGH University of Science and Technology
info@mateuszrzeczyca.pl
20.01.2019

*/

#ifndef VIDEOSTREAM_MENU_H
#define VIDEOSTREAM_MENU_H

#include "displayer.h"
#include "network.h"

class Menu : public Displayer, public Network
{
public:
    Menu();
    void menu();
    void startWatching();
    void configure();
    void usage();
    void changeIp();
    void changePort();
    void clearScreen();
};

#endif //VIDEOSTREAM_MENU_H
