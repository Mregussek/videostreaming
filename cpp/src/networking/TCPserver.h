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

        void define_socket();
        void define_sockaddr() override;
        void create_server_then_listen();
        void accept_incoming_connection();
        void send_data(cv::Mat, size_t);
        void close_connection();

        // just for inheriting
        void connect_to_server() {}
        void receive_data(unsigned char*, size_t) {}

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
