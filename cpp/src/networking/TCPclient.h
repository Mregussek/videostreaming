//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   30.03.2019

#ifndef VIDEOSTREAMING_TCPCLIENT_H
#define VIDEOSTREAMING_TCPCLIENT_H

#include "../inc_def.h"

namespace mrz
{
    class TCPclient {
    public:
        TCPclient();

        void define_socket();
        void define_sockaddr();
        void connect_to_server();
        void receive_data(unsigned char*, size_t&);
        void close_connection();

        void set_port(uint16_t);
        uint16_t get_port() const;

        void set_ip(std::string);
        std::string get_ip() const;

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
