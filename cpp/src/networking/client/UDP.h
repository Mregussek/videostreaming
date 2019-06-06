//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   11.05.2019

#ifndef VIDEOSTREAMING_UDPCLIENT_H
#define VIDEOSTREAMING_UDPCLIENT_H

#include "TCP.h"

namespace mrz
{
    /**
     * Implementation of UDP-based client class
     */
    class UDPclient
    {
    public:
        int* packet_size;
    private:
        int* sock_system_call;
        const char* ip;
        uint16_t* port;
        sockaddr_in* server;
        socklen_t* address_length;

    public:
        /**
         * Default constructor, actually does nothing
         */
        UDPclient();

        /**
        * Destructor, deallocates memory
        */
        ~UDPclient();

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
         * Sends data to UDP server
         *
         * @param buffer is that, what you are up to send
         * @param buffer_length is size of the buffer
         */
        void send_data(const void*, int);
    };
}


#endif //VIDEOSTREAMING_UDPCLIENT_H
