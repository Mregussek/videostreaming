//
// Created by mateusz on 22.04.19.
//

#include "TCPClient.h"

namespace mrz
{
    TCPClient::TCPClient() :
    sock_system_call( new int() ),
    ip( new char[sizeof "123.123.123.123"] ),
    port( new uint16_t(3305) ),
    server( new sockaddr_in() ),
    addr_length( new socklen_t( sizeof(sockaddr_in) ) ),
    recv_bytes( new ssize_t() )
    {
        strcpy(ip, "127.0.0.1");
    }

    TCPClient::TCPClient(char* i, char* p) :
    sock_system_call( new int() ),
    ip( new char[sizeof "123.123.123.123"] ),
    server( new sockaddr_in() ),
    port( new uint16_t() ),
    addr_length( new socklen_t( sizeof(sockaddr_in) ) ),
    recv_bytes( new ssize_t() )
    {
        ip = i;
        str_to_uint16(p, port);
    }

    TCPClient::~TCPClient()
    {
        delete sock_system_call;
        delete [] ip;
        delete port;
        delete server;
        delete addr_length;
        delete recv_bytes;
    }

    void TCPClient::create_socket()
    {
        *sock_system_call = socket(PF_INET, SOCK_STREAM, 0);

        if(*sock_system_call < 0)
            //handle_create_socket_client();
            exit(7);

        server->sin_family = PF_INET;
        server->sin_addr.s_addr = inet_addr(ip);
        server->sin_port = htons(*port);
    }

    void TCPClient::connect_to_server()
    {
        int* result = new int();
        auto converted = reinterpret_cast<sockaddr*>(server);

        *result = connect(*sock_system_call, converted, *addr_length);

        if(*result < 0)
            //handle_connect_to_server();
            exit(8);

        delete result;
    }

    void TCPClient::receive_data()
    {
        *recv_bytes = recv(*sock_system_call, recv_data, *recv_data_size, MSG_WAITALL);

        if(*recv_bytes < 0)
            //handle_receive_data();
            exit(9);
    }

    void TCPClient::close_connection()
    {
        close(*sock_system_call);
    }

    void TCPClient::str_to_uint16(const char *str, uint16_t *res)
    {
        char *end;
        errno = 0;
        long val = strtol(str, &end, 10);

        if (errno || end == str || *end != '\0' || val < 0 || val >= 0x10000)
            //handle_str_to_uint16();
            exit(10);

        *res = (uint16_t)val;
    }
}