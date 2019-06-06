//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   1.05.2019

#include "TCP.h"

namespace mrz
{
    TCPclient::TCPclient() {}

    void TCPclient::init_object(const char* set_ip, const char* set_port)
    {
        sock_system_call = new int;
        server = new sockaddr_in;
        address_length = new socklen_t( sizeof(sockaddr_in) );
        port = new uint16_t;

        ip = set_ip;
        char_to_uint16(set_port, port);
    }

    TCPclient::~TCPclient()
    {
        delete port;
        delete address_length;
        delete server;
        delete sock_system_call;
    }

    void TCPclient::define_socket()
    {
        *sock_system_call = socket(PF_INET, SOCK_STREAM, 0);

        if(*sock_system_call < 0)
        {
            std::cerr << "Cannot create TCP client socket!" << std::endl;
            exit(1);
        }

        server ->sin_family = PF_INET;
        server ->sin_addr.s_addr = inet_addr(ip);
        server ->sin_port = htons(*port);
    }

    void TCPclient::connect_to_server()
    {
        auto conv_sock = reinterpret_cast<sockaddr*>( server );

        std::cout << "Connecting to:\n";
        std::cout << "Address: " << inet_ntoa(server ->sin_addr)
        << " Port: " << *(this ->port) << "\n";

        int result;
        result = connect(*sock_system_call, conv_sock, *address_length);

        if(result < 0)
        {
            std::cerr << "Cannot connect to server!" << std::endl;
            exit(1);
        }

        std::cout << "Connected!" << std::endl;
    }

    void TCPclient::pair_metadata(uchar* recv_data)
    {
        metadata = recv_data;
    }

    void TCPclient::receive_data(const size_t* image_size)
    {
        ssize_t result = recv(*sock_system_call, metadata, *image_size, MSG_WAITALL);

        if(result < 0)
        {
            std::cerr << "Cannot receive data from server!" << std::endl;
            exit(1);
        }
    }

    void TCPclient::close_connection()
    {
        close(*sock_system_call);
    }
}