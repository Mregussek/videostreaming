//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   rzeczyca@student.agh.edu.pl
//   1.05.2019

#include "TCP.h"

namespace mrz
{
    TCPserver::TCPserver() {}

    void TCPserver::init_object(const char* set_port)
    {
        port = new uint16_t;
        server_socket = new int;
        client_socket = new int;
        server = new sockaddr_in;
        client = new sockaddr_in;
        address_length = new socklen_t( sizeof(sockaddr_in) );

        char_to_uint16(set_port, port);
    }

    TCPserver::~TCPserver()
    {
        delete address_length;
        delete client;
        delete server;
        delete client_socket;
        delete server_socket;
        delete port;
    }

    void TCPserver::define_socket()
    {
        *server_socket = socket(AF_INET, SOCK_STREAM, 0);

        if(*server_socket < 0)
        {
            std::cerr << "Cannot create TCP server socket!" << std::endl;
            exit(1);
        }

        server ->sin_family = AF_INET;
        server ->sin_addr.s_addr = INADDR_ANY;
        server ->sin_port = htons( *port );
    }

    void TCPserver::create_server_then_listen()
    {
        auto conv_sock = reinterpret_cast<sockaddr*>( server );

        int result = bind(*server_socket, conv_sock, *address_length);

        if(result < 0)
        {
            std::cerr << "Cannot bind TCP server socket!" << std::endl;
            exit(1);
        }

        listen(*server_socket, 1);

        std::cout << "TCP-based Server Started!\n" <<
                  "Server Address: " << inet_ntoa(server ->sin_addr) <<
                  " Server Port:" << *port << "\n";

        conv_sock = reinterpret_cast<sockaddr*>( client );

        *client_socket = accept(*server_socket, conv_sock, address_length);

        if(*client_socket < 0)
        {
            std::cerr << "Cannot accept connection from client" << std::endl;
            exit(1);
        }

        std::cout << "Connection Accepted!\n";
    }

    bool TCPserver::send_data(const size_t* size)
    {
        ssize_t result = send(*client_socket, metadata, *size, 0);

        if(result < 0)
        {
            std::cerr << "Cannot send data to the client!" << std::endl;
            return false;
        }

        return true;
    }

    void TCPserver::close_connection()
    {
        close( *server_socket );
        close( *client_socket );
    }

    void TCPserver::refresh_metadata(unsigned char* new_data)
    {
        metadata = new_data;
    }
}