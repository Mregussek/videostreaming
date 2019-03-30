//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   30.03.2019

#ifndef VIDEOSTREAMING_SERVER_H
#define VIDEOSTREAMING_SERVER_H

#include "networking/TCPserver.h"
#include "videoprocessing/VIDEOclient.h"
#include "inc_def.h"

namespace mrz
{
    class SERVER
    {
    public:
        void menu();

    private:
        void run();
        void change_port();

        void clear_screen()
        {
            std::cout << "\033[2J\033[1;1H";
        }

        void write_line()
        {
            std::cout << std::string(20, '-');
            std::cout << "\n";
        }

        TCPserver server;
        VIDEOclient camera;
    };

    void SERVER::menu()
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
                run();
                break;
            case 2:
                change_port();
                break;
            case 3:
                menu();
                break;
            case 4:
                exit(0);
            default:
                menu();
                break;
        }
    }

    void SERVER::change_port()
    {
        clear_screen();
        std::cout << "Current: " << server.get_port() << std::endl;
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
                server.set_port(number);
                break;
            default:
                change_port();
        }
    }

    void SERVER::run()
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

}

#endif //VIDEOSTREAMING_SERVER_H
