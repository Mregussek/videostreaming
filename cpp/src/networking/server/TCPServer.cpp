//
// Created by mateusz on 22.04.19.
//

#include "TCPServer.h"

namespace mrz
{
    TCPServer::TCPServer() :
    server_sock( new int() ),
    client_sock( new int() ),
    server( new sockaddr_in() ),
    client( new sockaddr_in() ),
    port( new uint16_t(3305) ),
    addr_length( new socklen_t() )
    {}

    TCPServer::TCPServer(char* p) :
    server_sock( new int() ),
    client_sock( new int() ),
    server( new sockaddr_in() ),
    client( new sockaddr_in() ),
    port( new uint16_t() ),
    addr_length( new socklen_t() )
    {
        str_to_uint16(p, port);
    }

    TCPServer::~TCPServer()
    {
        delete server_sock;
        delete client_sock;
        delete server;
        delete client;
        delete port;
        delete addr_length;
    }

    void TCPServer::create_socket()
    {
        *server_sock = socket(AF_INET, SOCK_STREAM, 0);

        if(*server_sock < 0)
            //handle_create_socket_server();
            exit(1);


        server ->sin_family = AF_INET;
        server ->sin_addr.s_addr = INADDR_ANY;
        server ->sin_port = htons(*port);
    }

    void TCPServer::create_server()
    {
        auto converted = reinterpret_cast<sockaddr*>(server);
        int* result = new int();

        *result = bind(*server_sock, converted, *addr_length);

        if(*result < 0)
            //handle_create_server();
            exit(1);

        delete result;

        listen(*server_sock, 1);

        converted = reinterpret_cast<sockaddr*>(client);

        *client_sock = accept(*server_sock, converted, addr_length);

        if(*client_sock < 0)
            //handle_accept_connection();
            exit(1);
    }

    void TCPServer::send_data()
    {
        ssize_t* result = new ssize_t();

        *result = send(*client_sock, data_to_send, *data_to_send_size, 0);

        if(*result < 0)
            //handle_send_data();

        delete result;
    }

    void TCPServer::close_connection()
    {
        close(*client_sock);
        close(*server_sock);
    }


    void TCPServer::str_to_uint16(const char *str, uint16_t *res)
    {
        char *end;
        errno = 0;
        long val = strtol(str, &end, 10);

        if (errno || end == str || *end != '\0' || val < 0 || val >= 0x10000)
            //handle_str_to_uint16t();
            exit(1);

        *res = (uint16_t)val;
    }
}