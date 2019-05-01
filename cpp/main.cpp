//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   1.05.2019

#include "src/Facade.h"

void give_right_arguments();

int main(int argc, char** argv)
{
    // server
    if(argc == 3)
        // ./video <port> = argv[1] <protocol> = argv[2]
        if(strcmp(argv[2], "tcp") == 0)
        {
            auto server = new mrz::Facade
                    (reinterpret_cast<mrz::ServerStrategy*>( new mrz::TCPserver(argv[1]) ));
            delete server;
        }
        else if(strcmp(argv[2], "udp") == 0)
        {
            return 0;
        }
        else
            give_right_arguments();
    // client
    else if(argc == 4)
        // ./video <server> = argv[1] <port> = argv[2] <protocol> = argv[3]
        if(strcmp(argv[3], "tcp") == 0)
        {
            auto client = new mrz::Facade
                    (reinterpret_cast<mrz::ClientStrategy*>( new mrz::TCPclient(argv[1], argv[2]) ));
            delete client;
        }
        else if(strcmp(argv[3], "udp") == 0)
        {
            return 0;
        }
        else
            give_right_arguments();
    else
        give_right_arguments();

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
