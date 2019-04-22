//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   30.03.2019

#ifndef VIDEOSTREAMING_CLIENT_H
#define VIDEOSTREAMING_CLIENT_H

#include "networking/client/TCPclient.h"
#include "videoprocessing/VIDEOserver.h"
#include "inc_def.h"

namespace mrz
{
    class CLIENT
    {
    public:
        void menu();

    private:
        void run();
        void change_port();
        void change_ip();

        TCPclient client;
        VIDEOserver display;
    };

    void CLIENT::menu()
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
                run();
                break;
            case 2:
                change_port();
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
                menu();
                break;
        }
    }

    void CLIENT::change_port()
    {
        clear_screen();
        std::cout << "Current: " << client.get_port() << std::endl;
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
                client.set_port(number);
                break;
            default:
                change_port();
        }
    }

    void CLIENT::change_ip()
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

    void CLIENT::run()
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
}

#endif //VIDEOSTREAMING_CLIENT_H
