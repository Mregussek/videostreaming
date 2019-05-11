//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   1.05.2019

#ifndef VIDEOSTREAMING_TCPSERVER_H
#define VIDEOSTREAMING_TCPSERVER_H

#include "../include.h"

namespace mrz
{
    class TCPserver {
    public:
        TCPserver(char*);
        ~TCPserver();

        void define_socket();
        void create_server_then_listen();
        void refresh_metadata(unsigned char*);
        bool send_data(size_t*);
        void close_connection();

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