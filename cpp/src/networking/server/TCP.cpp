//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   1.05.2019

#include "TCP.h"

namespace mrz
{
    TCPserver::TCPserver(char* set_port) :
    server_socket( new int ),
    client_socket( new int ),
    server( new sockaddr_in ),
    client( new sockaddr_in ),
    port( new uint16_t ),
    address_length( new socklen_t( sizeof(sockaddr_in)) ),
    sent_data( false )
    {
        char_to_uint16(set_port, this ->port);
    }

    TCPserver::~TCPserver()
    {
        delete port;
        delete server_socket;
        delete client_socket;
        delete server;
        delete client;
        delete address_length;
    }

    void TCPserver::define_socket()
    {
        *(this ->server_socket) = socket(AF_INET, SOCK_STREAM, 0);

        if(*(this ->server_socket) < 0)
            //Error::error_creating_socket();
            exit(3);

        this ->server ->sin_family = AF_INET;
        this ->server ->sin_addr.s_addr = INADDR_ANY;
        this ->server ->sin_port = htons(*(this ->port));
    }

    void TCPserver::create_server_then_listen()
    {
        auto conv_sock = reinterpret_cast<sockaddr*>( server );
        int* result = new int;

        *result = bind(*(this ->server_socket), conv_sock, *(this ->address_length));

        if(*result < 0)
            //Error::error_bind_server();
            exit(4);

        delete result;

        listen(*(this ->server_socket), 1);

        std::cout << "Waiting for connections...\n" <<
                  "Server Address: " << inet_ntoa(this ->server ->sin_addr) <<
                  " Server Port:" << *(this ->port) << "\n";

        conv_sock = reinterpret_cast<sockaddr*>( client );

        *(this ->client_socket) = accept(*(this ->server_socket), conv_sock, address_length);

        if(*(this ->client_socket) < 0)
            //Error::error_accept_connection();
            exit(5);

        std::cout << "Connection Accepted!\n";
    }

    bool TCPserver::send_data(size_t& size)
    {
        auto result = new ssize_t;
        *result = send(*(this ->client_socket), metadata, size, 0);

        if(*result < 0)
        {
            //Error::error_sending_data();
            delete result;
            return false;
        }

        delete result;
        return true;
    }

    void TCPserver::close_connection()
    {
        close( *(this ->server_socket) );
        close( *(this ->client_socket) );
    }

    void TCPserver::refresh_metadata(unsigned char* new_data)
    {
        this ->metadata = new_data;
    }
}