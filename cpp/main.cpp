//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   30.03.2019

#include "src/Facade.h"

void give_right_arguments();

int main(int argc, char* argv[])
{
    // server
    if(argc == 3)
        if(argv[2] == "tcp")
        {
            mrz::TCPServer* tcp = new mrz::TCPServer(argv[1]);
            mrz::Facade* server = new mrz::Facade( reinterpret_cast<mrz::ServerStrategy*>(tcp) );

            delete tcp;
            delete server;

        }
        else if(argv[2] == "udp")
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
        if(argv[3] == "tcp")
        {
            mrz::TCPClient* tcp = new mrz::TCPClient(argv[1], argv[2]);
            mrz::Facade* client = new mrz::Facade( reinterpret_cast<mrz::ClientStrategy*>(tcp) );

            delete tcp;
            delete client;
        }
        else if(argv[3] == "udp")
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
    std::cout << "\n\n Example:\n";
    std::cout << "video 3305 tcp\t\t (This will run server on 3305 "
        << "port with TCP protocol\n";
    std::cout << "video 192.168.201.78 3305 udp\t\t "
        << "(This will run client which connects to "
        << "192.168.201.78 on 3305 port with UDP protocol\n";

    exit(1);
}
