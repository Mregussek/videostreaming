//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   1.05.2019

#ifndef VIDEOSTREAMING_TCPCLIENT_H
#define VIDEOSTREAMING_TCPCLIENT_H

#include "../include.h"

namespace mrz
{
    class TCPclient {
    public:
        TCPclient(char*, char*);
        ~TCPclient();

        void define_socket();
        void connect_to_server();
        void pair_metadata(uchar*);
        void receive_data(const size_t*);
        void close_connection();

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