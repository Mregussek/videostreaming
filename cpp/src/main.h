//
// Created by mateusz on 16.03.19.
//

#ifndef CPP_MAIN_H
#define CPP_MAIN_H

#include "inc_def.h"

#include "networking/TCPserver.h"
#include "networking/TCPclient.h"
#include "videoprocessing/VIDEOclient.h"
#include "videoprocessing/VIDEOserver.h"

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
    VIDEOserver display;

    client.define_socket();
    client.define_sockaddr();
    client.connect_to_server();

    display.check_if_continuous();
    display.create_window();

    uchar* metadata = display.get_metadata();

    while (display.get_key() != 'q')
    {
        client.receive_data(metadata, display.get_image_size());

        display.show_image();

        if (display.wait() >= 0)
            break;
    }

    delete metadata;
    client.close_connection();
}

void mrz::menu::run_server()
{
    TCPserver server;
    VIDEOclient camera;

    server.define_socket();
    server.define_sockaddr();
    server.create_server_then_listen();

    camera.check_if_continuous();
    server.accept_incoming_connection();


    while(true)
    {
        camera.got_frame = camera.read_frame();

        if(!camera.got_frame)
            break;

        camera.process_image();

        server.sent_data = server.send_data(camera.gray_image, camera.get_image_size());

        if(!server.sent_data)
            break;
    }

    server.close_connection();
}

#endif //CPP_MAIN_H
