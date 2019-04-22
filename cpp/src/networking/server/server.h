//
// Created by mateusz on 22.04.19.
//

#ifndef VIDEOSTREAMING_SERVER_H
#define VIDEOSTREAMING_SERVER_H

// sockets
#include <sys/socket.h>

// sockaddr_in
#include <arpa/inet.h>

// close( <socket> )
#include <zconf.h>

// errno
#include <errno.h>

// strtol
#include <stdlib.h>

namespace mrz
{
    class ServerStrategy
    {
    public:
        virtual void create_socket() = 0;
        virtual void create_server() = 0;
        virtual void send_data() = 0;
        virtual void close_connection() = 0;

        virtual void set_port(uint16_t*) = 0;
    };

    void handle_create_socket_server() { }

    void handle_create_server() { }

    void handle_accept_connection() { }

    void handle_send_data() { }

    void handle_str_to_uint16() { }
}

#endif //VIDEOSTREAMING_SERVER_H
