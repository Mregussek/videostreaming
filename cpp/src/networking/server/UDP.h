//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   rzeczyca@student.agh.edu.pl
//   09.05.2019

#ifndef VIDEOSTREAMING_UDPSERVER_H
#define VIDEOSTREAMING_UDPSERVER_H

#include "TCP.h"

namespace mrz
{
    /**
     * Implementation of UDP-based server class
     */
    class UDPserver
    {
    public:
        int* recv_message;
        int* max_recv_message;

    private:
        int* sock_system_call;
        int* broadcast_permission;
        sockaddr_in* server;
        sockaddr_in* client;
        uint16_t* port;
        socklen_t* address_length;

    public:
        /**
         * Default constructor, actually does nothing
         */
        UDPserver();

        /**
         * Destructor, deallocates memory
         */
        ~UDPserver();

        /**
         * Allocates memory to all variables, then converts and sets port from char* to uint16_t*
         *
         * @param set_port stores port number in char*
         */
        void init_object(const char*);

        /**
         * Creates socket object and sets sockaddr_in variable
         */
        void define_socket();

        /**
         * Binds server and sets broadcast permission
         */
        void create_server_then_listen();

        /**
         * Receives data from client, server has no need to know anything about client
         *
         * @param buffer stores pointer to variable, which will have access to received dat
         * @param buffer_length stores expected length, which must be received
         */
        void receive_data(void* buffer, int buffer_length);

        /**
         * Closes connection
         */
        void close_connection();
    };
}

#endif //VIDEOSTREAMING_UDPSERVER_H
