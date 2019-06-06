//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   rzeczyca@student.agh.edu.pl
//   11.05.2019

#include "UDP.h"

namespace mrz
{
    UDPclient::UDPclient() {}

    void UDPclient::init_object(const char* set_ip, const char* set_port)
    {
        ip = set_ip;
        port = new uint16_t;

        sock_system_call = new int;
        server = new sockaddr_in;
        address_length = new socklen_t( sizeof(sockaddr_in) );
        packet_size = new int(4096);

        char_to_uint16(set_port, port);
    }

    UDPclient::~UDPclient()
    {
        delete packet_size;
        delete address_length;
        delete server;
        delete sock_system_call;
        delete port;
    }

    void UDPclient::define_socket()
    {
        *sock_system_call = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

        if(*sock_system_call < 0)
        {
            std::cerr << "Cannot create UDP client socket!" << std::endl;
            exit(1);
        }

        server ->sin_family = AF_INET;
        server ->sin_addr.s_addr = inet_addr(ip);
        server ->sin_port = htons(*port);
    }

    void UDPclient::send_data(const void* buffer, int buffer_length)
    {
        auto conv = reinterpret_cast<sockaddr*>(server);

        int result = sendto(*sock_system_call, buffer, buffer_length, 0, conv, *address_length);

        if(result != buffer_length)
        {
            std::cerr << "Sent data does not match buffer length!" << std::endl;
            exit(1);
        }
    }
}
