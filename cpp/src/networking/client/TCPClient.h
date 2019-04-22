//
// Created by mateusz on 22.04.19.
//

#ifndef VIDEOSTREAMING_TCPCLIENT_H
#define VIDEOSTREAMING_TCPCLIENT_H

#include "client.h"

namespace mrz
{
    class TCPClient : public ClientStrategy
    {
    public:
        TCPClient();
        TCPClient(char*, char*);
        ~TCPClient();

        void create_socket() override;
        void connect_to_server() override;
        void receive_data() override;
        void close_connection() override;

        void str_to_uint16(const char*, uint16_t*);

        unsigned char* recv_data;
        size_t* recv_data_size;

    private:
        int* sock_system_call;
        char* ip;
        uint16_t* port;
        sockaddr_in* server;
        socklen_t* addr_length;
        ssize_t* recv_bytes;
    };
}


#endif //VIDEOSTREAMING_TCPCLIENT_H
