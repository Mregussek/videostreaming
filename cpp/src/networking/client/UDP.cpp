//
// Created by mateusz on 01.05.19.
//

#include "UDP.h"

namespace mrz
{
    UDPclient::UDPclient(char* set_ip, char* set_port) :
    host( new hostent ),
    port( new uint16_t ),
    server( new sockaddr_in ),
    sock_system_call( new int ),
    ip( set_ip ),
    packet_size( new int(4096) )
    {
        char_to_uint16(set_port, port);
    }

    UDPclient::~UDPclient()
    {
        delete host;
        delete port;
        delete server;
        delete sock_system_call;
	    delete packet_size;
    }

    void UDPclient::define_socket()
    {
        *sock_system_call = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

        if(*sock_system_call < 0)
            exit(2);

        host = gethostbyname(ip);

        if(host == nullptr)
            exit(3);

        server ->sin_family = AF_INET;
        server ->sin_addr.s_addr = *((unsigned long*) host->h_addr_list[0]);
        server ->sin_port = htons(*port);
    }

    void UDPclient::send_data(const void* buffer, int buffer_length)
    {
        auto conv = reinterpret_cast<sockaddr*>(server);
        int* result = new int;

        *result = sendto(*sock_system_call, (void*) buffer, buffer_length, 0, conv, sizeof(sockaddr_in));

        if(*result != buffer_length)
            exit(5);

        delete result;
    }
}
