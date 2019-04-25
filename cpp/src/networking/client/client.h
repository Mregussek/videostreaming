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

        unsigned char* recv_data;
        size_t* recv_data_size;
    };
}

#endif //VIDEOSTREAMING_CLIENT_H
