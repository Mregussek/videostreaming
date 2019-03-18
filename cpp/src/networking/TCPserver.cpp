//
// Created by mateusz on 16.03.19.
//

#include "TCPserver.h"

namespace mrz
{
    TCPserver::TCPserver() :
    port(3305),
    address_length(sizeof(sockaddr_in)),
    sent_data( false )
    {}


    void TCPserver::define_socket()
    {
        this ->server_socket = socket(AF_INET, SOCK_STREAM, 0);

        if(this ->server_socket < 0)
            Error::error_creating_socket();
    }

    void TCPserver::define_sockaddr()
    {
        this ->server.sin_family = AF_INET;
        this ->server.sin_addr.s_addr = INADDR_ANY;
        this ->server.sin_port = htons(this ->port);
    }

    void TCPserver::create_server_then_listen()
    {
        auto conv_sock = reinterpret_cast<sockaddr*>( &(this ->server) );
        int* result = new int;

        *result = bind(this ->server_socket, conv_sock, this ->address_length);

        if(*result < 0)
            Error::error_bind_server();

        delete result;

        listen(this ->server_socket, 1);

        std::cout <<  "Waiting for connections...\n" <<
                  "Server Address: " << inet_ntoa(this ->server.sin_addr) <<
                  " Server Port:" << this ->port << "\n";
    }

    void TCPserver::accept_incoming_connection()
    {
        auto conv_sock = reinterpret_cast<sockaddr*>( &(this ->client) );
        auto conv_point = &(this ->address_length);

        this ->client_socket = accept(this ->server_socket, conv_sock, conv_point);

        if(this ->client_socket < 0)
            Error::error_accept_connection();

        std::cout << "Connection Accepted!\n";
    }

    bool TCPserver::send_data(cv::Mat image, size_t size)
    {
        ssize_t* result = new ssize_t;
        *result = send(this ->client_socket, image.data, size, 0);

        if(*result < 0)
        {
            Error::error_sending_data();
            delete result;
            return false;
        }

        delete result;
        return true;
    }

    void TCPserver::close_connection()
    {
        close(this ->server_socket);
        close(this ->client_socket);
    }
}