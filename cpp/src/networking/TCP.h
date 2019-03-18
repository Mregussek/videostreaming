//
// Created by mateusz on 16.03.19.
//

#ifndef VIDEOSTREAMING_TCP_H
#define VIDEOSTREAMING_TCP_H

#include "../inc_def.h"

namespace mrz
{
    class TCP
    {
    public:
        virtual void define_socket() = 0;
        virtual void define_sockaddr() = 0;
        virtual void close_connection() = 0;

        // for client
        virtual void connect_to_server() = 0;
        virtual void receive_data(unsigned char*, size_t) = 0;

        // for server
        virtual void create_server_then_listen() = 0;
        virtual void accept_incoming_connection() = 0;
        virtual bool send_data(cv::Mat, size_t) = 0;
    };

    class Error
    {
    public:
        static void error_creating_socket() {}
        static void error_connecting_to_server() {}
        static void error_bind_server() {}
        static void error_accept_connection() {}
        static void error_sending_data() {}
    };
}

/*
void mrz::TCP::define_socket() {}
void mrz::TCP::define_sockaddr() {}
void mrz::TCP::close_connection() {}

// for client
void mrz::TCP::connect_to_server() {}
void mrz::TCP::receive_data(unsigned char*, size_t) {}

// for server
void mrz::TCP::create_server_then_listen() {}
void mrz::TCP::accept_incoming_connection() {}
void mrz::TCP::send_data(cv::Mat, size_t) {}
 */

//mrz::TCP::TCP() {}
//mrz::TCP::~TCP() {}

#endif //VIDEOSTREAMING_TCP_H
