//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   1.05.2019

#include "TCP.h"

namespace mrz
{
    TCPclient::TCPclient(char* set_ip, char* set_port) :
    sock_system_call( new int ),
    ip( set_ip ),
    port( new uint16_t ),
    server( new sockaddr_in ),
    address_length( new socklen_t( sizeof(sockaddr_in)) ),
    received_bytes( new ssize_t(0) )
    {
        char_to_uint16(set_port, this ->port);
    }

    TCPclient::~TCPclient()
    {
        delete port;
        delete sock_system_call;
        delete server;
        delete address_length;
        delete received_bytes;
    }

    void TCPclient::define_socket()
    {
        *(this ->sock_system_call) = socket(PF_INET, SOCK_STREAM, 0);

        if(*(this ->sock_system_call) < 0)
        {
            std::cerr << "Cannot create TCP client socket!" << std::endl;
            exit(1);
        }

        server ->sin_family = PF_INET;
        server ->sin_addr.s_addr = inet_addr(ip);
        server ->sin_port = htons(*(this ->port));
    }

    void TCPclient::connect_to_server()
    {
        int* result = new int;
        auto conv_sock = reinterpret_cast<sockaddr*>( server );

        std::cout << "Connecting to:\n";
        std::cout << "Address: " << inet_ntoa(this ->server ->sin_addr)
        << " Port: " << *(this ->port) << "\n";

        *result = connect(*(this ->sock_system_call), conv_sock, *(this ->address_length));

        if(*result < 0)
        {
            std::cerr << "Cannot connect to server!" << std::endl;
            exit(1);
        }

        std::cout << "Connected!" << std::endl;

        delete result;
    }

    void TCPclient::pair_metadata(uchar* recv_data)
    {
        this ->metadata = recv_data;
    }

    void TCPclient::receive_data(const size_t* image_size)
    {
        *(this ->received_bytes) = recv(*(this ->sock_system_call), metadata, *image_size, MSG_WAITALL);

        if(*received_bytes < 0)
        {
            std::cerr << "Cannot receive data from server!" << std::endl;
            exit(1);
        }
    }

    void TCPclient::close_connection()
    {
        close(*(this ->sock_system_call));
    }
}