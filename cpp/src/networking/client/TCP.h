//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   rzeczyca@student.agh.edu.pl
//   1.05.2019

#ifndef VIDEOSTREAMING_TCPCLIENT_H
#define VIDEOSTREAMING_TCPCLIENT_H

#include "../../../include/include.h"

namespace mrz
{
    /**
     * Implementation of TCP-based client class
     */
    class TCPclient
    {
        int* sock_system_call;
        const char* ip;
        uint16_t* port;
        sockaddr_in* server;
        socklen_t* address_length;
        unsigned char* metadata;

    public:
        /**
         * Default constructor, actually does nothing
         */
        TCPclient();

        /**
        * Destructor, deallocates memory
        */
        ~TCPclient();

        /**
         * Allocates memory to all variables, then converts and sets port from char* to uint16_t*
         *
         * @param set_ip stores IP address in char*
         * @param set_port stores port number in char*
         */
        void init_object(const char* set_ip, const char* set_port);

        /**
         * Creates socket object and sets sockaddr_in variable
         */
        void define_socket();

        /**
         * Connects to specified server
         */
        void connect_to_server();

        /**
         * Pairs metadata for the whole program, you should use it before app starts
         *
         * @param recv_data will be paired with class variable metadata
         */
        void pair_metadata(uchar* recv_data);

        /**
         * Receive data from the server
         *
         * @param image_size is variable which stores how long received message will be
         */
        void receive_data(const size_t* image_size);

        /**
         * Closes connection
         */
        void close_connection();
    };
}

#endif //VIDEOSTREAMING_TCPCLIENT_H