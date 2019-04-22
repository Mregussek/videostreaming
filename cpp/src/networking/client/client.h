//
// Created by mateusz on 22.04.19.
//

#ifndef VIDEOSTREAMING_CLIENT_H
#define VIDEOSTREAMING_CLIENT_H

// sockets
#include <sys/socket.h>

// sockaddr_in
#include <arpa/inet.h>

// close( <socket> )
#include <zconf.h>

// strcpy
#include <string.h>

// errno
#include <errno.h>

// strtol
#include <stdlib.h>

namespace mrz
{
    class ClientStrategy
    {
    public:
        virtual void create_socket() = 0;
        virtual void connect_to_server() = 0;
        virtual void receive_data() = 0;
        virtual void close_connection() = 0;
    };

    void handle_create_socket_client() { }

    void handle_connect_to_server() { }

    void handle_receive_data() { }

    void handle_str_to_uint16() { }
}

#endif //VIDEOSTREAMING_CLIENT_H
