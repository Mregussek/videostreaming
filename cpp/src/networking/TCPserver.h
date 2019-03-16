//
// Created by mateusz on 16.03.19.
//

#ifndef VIDEOSTREAMING_TCPSERVER_H
#define VIDEOSTREAMING_TCPSERVER_H

// inheriting from TCP
#include "TCP.h"

namespace mrz
{
    class TCPserver : public TCP {
    public:
        TCPserver();

        void define_socket() override;
        void define_sockaddr() override;
        void create_server_then_listen() override;
        void accept_incoming_connection() override;
        void send_data(cv::Mat, size_t) override;
        void close_connection() override;

    private:
        int server_socket;
        int client_socket;
        uint16_t port;
        sockaddr_in server;
        sockaddr_in client;
        socklen_t address_length;
    };
}



#endif //VIDEOSTREAMING_TCPSERVER_H
