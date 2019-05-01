//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   1.05.2019

#ifndef VIDEOSTREAMING_TCPSERVER_H
#define VIDEOSTREAMING_TCPSERVER_H

#include "../include.h"
#include "ServerStrategy.h"

namespace mrz
{
    class TCPserver : ServerStrategy {
    public:
        TCPserver(char*);
        ~TCPserver();

        void define_socket() override;
        void create_server_then_listen() override;
        void refresh_metadata(unsigned char*) override;
        bool send_data(size_t*) override;
        void close_connection() override;

        bool sent_data;
    private:
        unsigned char* metadata;
        int* server_socket;
        int* client_socket;
        uint16_t* port;
        sockaddr_in* server;
        sockaddr_in* client;
        socklen_t* address_length;
    };
}

#endif //VIDEOSTREAMING_TCPSERVER_H