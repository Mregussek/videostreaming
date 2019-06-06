//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   rzeczyca@student.agh.edu.pl
//   1.05.2019

#ifndef VIDEOSTREAMING_FACADE_H
#define VIDEOSTREAMING_FACADE_H

#include <iostream>

// include all files to Facade
#include "networking/client/UDP.h"
#include "networking/server/UDP.h"
#include "videoprocessing/Camera.h"
#include "videoprocessing/Displayer.h"

namespace mrz
{
    /*
     * Class created to apply Facade design pattern
     */
    class Facade {
    public:
        Facade();

        /*
         *  Initialize TCP-based client script
         *
         *  @param client Pointer to class that handles TCP-client connection
         */
        static void init_client_tcp(TCPclient* client);

        /*
         *  Initialize TCP-based server script
         *
         *  @param client Pointer to class that handles TCP-server connection
         */
        static void init_server_tcp(TCPserver*);

        /*
         *  Initialize UDP-based client script
         *
         *  @param client Pointer to class that handles UDP-client connection
         */
        static void init_client_udp(UDPclient*);

        /*
         *  Initialize UDP-based server script
         *
         *  @param client Pointer to class that handles UDP-server connection
         */
        static void init_server_udp(UDPserver*);
    };
}

#endif //VIDEOSTREAMING_FACADE_H
