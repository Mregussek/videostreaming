//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
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
    class Facade {
    public:
        explicit Facade(TCPserver*);
        explicit Facade(TCPclient*);
        explicit Facade(UDPserver*);
        explicit Facade(UDPclient*);
        void run_client_tcp(TCPclient*);
        void run_server_tcp(TCPserver*);
        void run_client_udp(UDPclient*);
        void run_server_udp(UDPserver*);
    };
}

#endif //VIDEOSTREAMING_FACADE_H
