//
// Created by mateusz on 22.04.19.
//

#ifndef VIDEOSTREAMING_TCPSERVER_H
#define VIDEOSTREAMING_TCPSERVER_H

#include "server.h"

namespace mrz
{
    class TCPServer : public ServerStrategy
    {
    public:
        TCPServer();
        TCPServer(char*);
        ~TCPServer();

        void create_socket() override;
        void create_server() override;
        void send_data() override;
        void close_connection() override;

        void str_to_uint16(const char*, uint16_t*);

        unsigned char* data_to_send;
        size_t* data_to_send_size;

    private:
        int* server_sock;
        int* client_sock;
        sockaddr_in* server;
        sockaddr_in* client;
        uint16_t* port;
        socklen_t* addr_length;
    };
}


#endif //VIDEOSTREAMING_TCPSERVER_H
