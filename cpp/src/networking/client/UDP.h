//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   11.05.2019

#ifndef VIDEOSTREAMING_UDPCLIENT_H
#define VIDEOSTREAMING_UDPCLIENT_H

#include "TCP.h"

namespace mrz
{
    class UDPclient
    {
    public:
        UDPclient(char*, char*);
        ~UDPclient();

        void define_socket();
        void send_data(const void*, int);
	
	    int* packet_size;
    private:
        int* sock_system_call;
        char* ip;
        uint16_t* port;
        sockaddr_in* server;
        socklen_t* address_length;
    };
}


#endif //VIDEOSTREAMING_UDPCLIENT_H
