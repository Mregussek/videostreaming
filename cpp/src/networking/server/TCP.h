//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   rzeczyca@student.agh.edu.pl
//   1.05.2019

#ifndef VIDEOSTREAMING_TCPSERVER_H
#define VIDEOSTREAMING_TCPSERVER_H

#include "../../../include/include.h"

namespace mrz
{
    /**
     * Implementation of TCP-based server class
     */
    class TCPserver
    {
        unsigned char* metadata;
        int* server_socket;
        int* client_socket;
        uint16_t* port;
        sockaddr_in* server;
        sockaddr_in* client;
        socklen_t* address_length;

    public:
        /**
         * Default constructor, actually does nothing
         */
        TCPserver();

        /**
         * Destructor, deallocates memory
         */
        ~TCPserver();

        /**
         * Allocates memory to all variables, then converts and sets port from char* to uint16_t*
         *
         * @param set_port stores port number in char*
         */
        void init_object(const char* set_port);

        /**
         * Creates socket object and sets sockaddr_in variable
         */
        void define_socket();

        /**
         * Binds server, waits for connection and accepts and first incoming one
         */
        void create_server_then_listen();

        /**
         * Assigns new metadata to class metadata variable
         *
         * @param new_data stores new metadata
         */
        void refresh_metadata(unsigned char* new_data);

        /**
         * Sends data to client, whose data was got by accepting connection
         *
         * @param size of message, which is sent
         * @return bool dependently of success, true for properly delivered message
         */
        bool send_data(const size_t* size);

        /**
         * Closes connection
         */
        void close_connection();
    };
}

#endif //VIDEOSTREAMING_TCPSERVER_H