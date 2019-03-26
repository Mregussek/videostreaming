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

    void menu_client();
    void menu_server();

    void run_server();
    void run_client();

    void clear_screen()
    {
        std::cout << "\033[2J\033[1;1H";
    }

    void write_line()
    {
        std::cout << std::string(20, '-');
        std::cout << "\n";
    }

private:
    template<typename T>
    void change_port(T&);

    void change_ip();

    TCPclient client;
    VIDEOserver display;
    TCPserver server;
    VIDEOclient camera;
};

void mrz::menu::start()
{
    clear_screen();
    std::cout << "1. SERVER (RPi)\n";
    std::cout << "2. CLIENT (Other machine)\n";
    std::cout << "3. Exit" << std::endl;
    std::cout << "Decide: ";
    int number;
    std::cin >> number;

    switch(number)
    {
        case 1:
            menu_server();
            break;
        case 2:
            menu_client();
            break;
        case 3:
            exit(0);
        default:
            clear_screen();
            menu();
    }
}

void mrz::menu::menu_server()
{
    clear_screen();

    std::cout << "Current Settings:\n";
    std::cout << "IP: Every Address / Port: " << server.get_port() << "\n";
    write_line();

    std::cout << "1. Start server\n";
    std::cout << "2. Change port\n";
    std::cout << "3. Back\n";
    std::cout << "4. Exit" << std::endl;
    std::cout << "Decide: ";
    int number;
    std::cin >> number;

    switch (number)
    {
        case 1:
            run_server();
            break;
        case 2:
            change_port(server);
            break;
        case 3:
            menu();
            break;
        case 4:
            exit(0);
        default:
            menu_server();
            break;
    }
}

void mrz::menu::menu_client()
{
    clear_screen();

    std::cout << "Current Settings:\n";
    std::cout << "IP: " << client.get_ip() << " / Port: " << client.get_port() << "\n";
    write_line();

    std::cout << "1. Start client\n";
    std::cout << "2. Change port\n";
    std::cout << "3. Change IP\n";
    std::cout << "4. Back\n";
    std::cout << "5. Exit" << std::endl;
    std::cout << "Decide: ";
    int number;
    std::cin >> number;

    switch (number)
    {
        case 1:
            run_client();
            break;
        case 2:
            change_port(server);
            break;
        case 3:
            change_ip();
            break;
        case 4:
            menu();
            break;
        case 5:
            exit(0);
        default:
            menu_server();
            break;
    }
}

template <typename T>
void mrz::menu::change_port(T& ser_cli)
{
    clear_screen();
    std::cout << "Current: " << ser_cli.get_port() << std::endl;
    std::cout << "Change to: ";
    uint16_t number;
    std::cin >> number;

    std::cout << "New Port: " << number << std::endl;
    std::cout << "Is this correct? [Y/N]: ";
    char good;
    std::cin >> good;

    switch(good)
    {
        case 'y':
        case 'Y':
            ser_cli.set_port(number);
            break;
        default:
            change_port(ser_cli);
    }
}

void mrz::menu::change_ip()
{
    clear_screen();
    std::cout << "Current: " << client.get_ip() << std::endl;
    std::cout << "Change to: ";
    std::string number;
    std::cin >> number;

    std::cout << "New IP: " << number << std::endl;
    std::cout << "Is this correct? [Y/N]: ";
    char good;
    std::cin >> good;

    switch(good)
    {
        case 'y':
        case 'Y':
            client.set_ip(number);
            break;
        default:
            change_ip();
    }
}

void mrz::menu::run_client()
{
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
