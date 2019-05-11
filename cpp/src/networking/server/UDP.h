//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   09.05.2019

#ifndef VIDEOSTREAMING_UDPSERVER_H
#define VIDEOSTREAMING_UDPSERVER_H

#include "TCP.h"

namespace mrz
{
    class UDPserver
    {
    public:
        UDPserver(char*);
        ~UDPserver();

        void define_socket();
        void create_server_then_listen();
        void receive_data(void*, int);
        void close_connection();

        int* recv_message;
        int* max_recv_message;
    private:
        int* sock_system_call;
        int* broadcast_permission;
        sockaddr_in* server;
        sockaddr_in* client;
        uint16_t* port;
        socklen_t* address_length;
    };
}

#endif //VIDEOSTREAMING_UDPSERVER_H
