//
// Created by mateusz on 16.03.19.
//

#ifndef CPP_MAIN_H
#define CPP_MAIN_H

#include "inc_def.h"

#include "networking/TCPserver.h"
#include "networking/TCPclient.h"

namespace mrz
{
    class menu;
}

class mrz::menu
{
public:
    void start();

    void run_server();
    void run_client();
};

void mrz::menu::start()
{
    int number;
    std::cin >> number;

    switch(number)
    {
        case 1:
            run_client();
            break;
        case 2:
            run_server();
            break;
        default:
            exit(0);
    }
}

void mrz::menu::run_client()
{
    TCPclient client;

}

void mrz::menu::run_server()
{
    TCPserver server;
}

#endif //CPP_MAIN_H
