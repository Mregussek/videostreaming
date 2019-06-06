//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   1.05.2019

// Managing parameters
//#include <argp.h>

// My project files
#include "src/Facade.h"

void give_right_arguments();

int main(int argc, char** argv)
{
    switch(argc)
    {
        // ./video <port> = argv[1] <protocol> = argv[2]
        case 3:
            if(strcmp(argv[2], "tcp") == 0)
            {
                mrz::TCPserver server;

                server.init_object(argv[1]);
                mrz::Facade::init_server_tcp(&server);
            }
            else if(strcmp(argv[2], "udp") == 0)
            {
                mrz::UDPserver server;

                server.init_object(argv[1]);
                mrz::Facade::init_server_udp(&server);
            }
            else
                give_right_arguments();
            break;
        // ./video <server> = argv[1] <port> = argv[2] <protocol> = argv[3]
        case 4:
            if(strcmp(argv[3], "tcp") == 0)
            {
                mrz::TCPclient client;

                client.init_object(argv[1], argv[2]);
                mrz::Facade::init_client_tcp(&client);
            }
            else if(strcmp(argv[3], "udp") == 0)
            {
                mrz::UDPclient client;

                client.init_object(argv[1], argv[2]);
                mrz::Facade::init_client_udp(&client);
            }
            else
                give_right_arguments();
            break;
        default:
            give_right_arguments();
            break;
    }

    return 0;
}

void give_right_arguments()
{
    std::cout << "For Client App: ";
    std::cout << "<Server Address> <Server Port> <Protocol>\n";
    std::cout << "For Server App: ";
    std::cout << "<Server Port> <Protocol>\n";
    std::cout << "\nExample:\n";
    std::cout << "./video 3305 tcp\n";
    std::cout << "./video 192.168.201.78 3305 udp\n";

    exit(1);
}
