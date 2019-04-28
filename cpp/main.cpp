//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   30.03.2019

#include "src/Facade.h"

void give_right_arguments();

int main(int argc, char** argv)
{
    // server
    if(argc == 3)
        if(strcmp(argv[2], "tcp") == 0)
        {
            mrz::TCPServer* tcp = new mrz::TCPServer(argv[1]);
            mrz::Facade* server = new mrz::Facade( reinterpret_cast<mrz::ServerStrategy*>(tcp) );

            delete tcp;
            delete server;

        }
        else if(strcmp(argv[2], "udp") == 0)
        {
            return 0;
            //mrz::UDPServer* udp = new mrz::UDPServer(argv[1]);
            //mrz::Facade* server = new mrz::Facade( reinterpret_cast<mrz::ServerStrategy*>(udp) );

            //delete udp;
            //delete server;
        }
        else
            give_right_arguments();
    // client
    else if(argc == 4)
        if(strcmp(argv[3], "tcp") == 0)
        {
            mrz::TCPClient* tcp = new mrz::TCPClient(argv[1], argv[2]);
            mrz::Facade* client = new mrz::Facade( reinterpret_cast<mrz::ClientStrategy*>(tcp) );

            delete tcp;
            delete client;
        }
        else if(strcmp(argv[3], "udp") == 0)
        {
            return 0;
            //mrz::UDPClient* udp = new mrz::UDPClient(argv[1], argv[2]);
            //mrz::Facade* client = new mrz::Facade( reinterpret_cast<mrz::ClientStrategy*>(udp) );

            //delete udp;
            //delete client;
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
    std::cout << "\n\nExample:\n";
    std::cout << "video 3305 tcp\n";
    std::cout << "video 192.168.201.78 3305 udp\n";

    exit(1);
}
