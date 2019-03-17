//
// Created by mateusz on 16.03.19.
//

#ifndef VIDEOSTREAMING_TCPCLIENT_H
#define VIDEOSTREAMING_TCPCLIENT_H

// inheriting from TCP
#include "TCP.h"

namespace mrz
{
    class TCPclient : public TCP {
    public:
        TCPclient();

        void define_socket() override;
        void define_sockaddr() override;
        void connect_to_server() override;
        void receive_data(unsigned char*, size_t) override;
        void close_connection() override;

        //just for inheriting
        void send_data(cv::Mat, size_t) {}
        void accept_incoming_connection() {}
        void create_server_then_listen() {}

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
