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

        unsigned char* data_to_send;
        size_t* data_to_send_size;
    };
}

#endif //VIDEOSTREAMING_SERVER_H
