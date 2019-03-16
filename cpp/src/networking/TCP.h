//
// Created by mateusz on 16.03.19.
//

#ifndef VIDEOSTREAMING_TCP_H
#define VIDEOSTREAMING_TCP_H

#include "../inc_def.h"

namespace mrz
{
    class TCP;
}

class mrz::TCP
{
public:
    virtual void define_socket();
    virtual void define_sockaddr();
    virtual void close_connection() ;

    // for client
    virtual void connect_to_server();
    virtual void receive_data(unsigned char*, size_t);

    // for server
    virtual void create_server_then_listen();
    virtual void accept_incoming_connection();
    virtual void send_data(cv::Mat, size_t);

protected:
    void error_creating_socket();
    void error_connecting_to_server();
    void error_bind_server();
    void error_accept_connection();
    void error_sending_data();
};

void mrz::TCP::error_creating_socket()
{

}

void mrz::TCP::error_connecting_to_server()
{

}

void mrz::TCP::error_bind_server()
{

}

void mrz::TCP::error_accept_connection()
{

}

void mrz::TCP::error_sending_data()
{

}

#endif //VIDEOSTREAMING_TCP_H
