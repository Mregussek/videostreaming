//
// Created by mateusz on 01.05.19.
//

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

    private:
        int* sock_system_call;
        char* ip;
        uint16_t* port;
        sockaddr_in* server;
        hostent* host;
    };
}


#endif //VIDEOSTREAMING_UDPCLIENT_H
