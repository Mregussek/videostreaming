//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   1.05.2019

#ifndef VIDEOSTREAMING_TCPCLIENT_H
#define VIDEOSTREAMING_TCPCLIENT_H

#include "../include.h"
#include "ClientStrategy.h"

namespace mrz
{
    class TCPclient : ClientStrategy {
    public:
        TCPclient(char*, char*);
        ~TCPclient();

        void define_socket() override;
        void connect_to_server() override;
        void pair_metadata(uchar*) override;
        void receive_data(size_t*) override;
        void close_connection() override;

    private:
        int* sock_system_call;
        char* ip;
        uint16_t* port;
        sockaddr_in* server;
        socklen_t* address_length;
        ssize_t* received_bytes;
        unsigned char* metadata;
    };
}

#endif //VIDEOSTREAMING_TCPCLIENT_H