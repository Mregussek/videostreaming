//
// Created by mateusz on 16.03.19.
//

#ifndef VIDEOSTREAMING_TCPCLIENT_H
#define VIDEOSTREAMING_TCPCLIENT_H

// inheriting from TCP
#include "../inc_def.h"

namespace mrz
{
    class TCPclient {
    public:
        TCPclient();

        void define_socket();
        void define_sockaddr();
        void connect_to_server();
        void receive_data(unsigned char*, size_t);
        void close_connection();

    private:
        int sock_system_call;
        std::string ip;
        uint16_t port;
        sockaddr_in server;
        socklen_t address_length;
        ssize_t received_bytes;
    };
}



#endif //VIDEOSTREAMING_TCPCLIENT_H
