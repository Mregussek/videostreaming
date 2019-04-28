//
// Created by mateusz on 22.04.19.
//

#ifndef VIDEOSTREAMING_FACADE_H
#define VIDEOSTREAMING_FACADE_H

/*
 * Why I include only UDPClient and UDPServer only?
 * My idea is to avoid re-definition error, when trying
 * to include all source files into one header.
 * client.h starts, TCPClient.h includes client.h
 * and afterwards UDPClient.h includes TCPClient.h
 * The same happens in server directory.
 */
#include "networking/client/UDPClient.h"
#include "networking/server/UDPServer.h"
#include "videoprocessing/Displayer.h"

#include <iostream>

namespace mrz
{
    class Facade
    {
    public:
        Facade(ClientStrategy*);
        Facade(ServerStrategy*);

        void run_server();
        void run_client();

    private:
        ClientStrategy* client;
        ServerStrategy* server;
        Camera* cam;
        Displayer* display;
        int test;
    };
}

#endif //VIDEOSTREAMING_FACADE_H
