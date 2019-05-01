//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   1.05.2019

#ifndef VIDEOSTREAMING_FACADE_H
#define VIDEOSTREAMING_FACADE_H

#include <iostream>

// include all files to Facade
#include "networking/client/TCP.h"
#include "networking/server/TCP.h"
#include "videoprocessing/Camera.h"
#include "videoprocessing/Displayer.h"

namespace mrz
{
    class Facade {
    public:
        explicit Facade(ClientStrategy*);
        explicit Facade(ServerStrategy*);
        void run_client(ClientStrategy*);
        void run_server(ServerStrategy*);
    };
}

#endif //VIDEOSTREAMING_FACADE_H
