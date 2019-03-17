//
// Created by mateusz on 16.03.19.
//

#include "TCPclient.h"

namespace mrz
{
    TCPclient::TCPclient() :
    ip("127.0.0.1"),
    port(3305),
    address_length(sizeof(sockaddr_in)),
    received_bytes(0)
    {}

    void TCPclient::define_socket()
    {
        this ->sock_system_call = socket(PF_INET, SOCK_STREAM, 0);

        if(this ->sock_system_call < 0)
            Error::error_creating_socket();
    }

    void TCPclient::define_sockaddr()
    {
        char* ip_chars = new char[this ->ip.length() + 1];
        strcpy(ip_chars, this ->ip.c_str());

        server.sin_family = PF_INET;
        server.sin_addr.s_addr = inet_addr(ip_chars);
        server.sin_port = htons(this ->port);

        delete [] ip_chars;
    }

    void TCPclient::connect_to_server()
    {
        int* result = new int;
        auto conv_sock = reinterpret_cast<sockaddr*>( &(this ->server) );

        *result = connect(this ->sock_system_call, conv_sock, this ->address_length);

        if(*result < 0)
            Error::error_connecting_to_server();

        delete result;
    }

    void TCPclient::receive_data(unsigned char* metadata, size_t image_size)
    {
        this ->received_bytes = recv(this ->sock_system_call, metadata, image_size, MSG_WAITALL);
    }

    void TCPclient::close_connection()
    {
        close(this ->sock_system_call);
    }
}
