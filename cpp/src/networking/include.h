//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   1.05.2019

#ifndef VIDEOSTREAMING_INCLUDE_H
#define VIDEOSTREAMING_INCLUDE_H

// for networking
#include <sys/socket.h> // sockets
#include <arpa/inet.h> // sockaddr_in
#include <netdb.h> // hostent

// close
#include <zconf.h>

// opencv
#include <opencv2/opencv.hpp>

// vector
#include <vector>

namespace mrz
{
    inline void char_to_uint16(const char *str, uint16_t *res)
    {
        char *end;
        errno = 0;
        long val = strtol(str, &end, 10);

        if (errno || end == str || *end != '\0' || val < 0 || val >= 0x10000)
            //handle_str_to_uint16();
            exit(10);

        *res = (uint16_t)val;
    }
}

#endif //VIDEOSTREAMING_INCLUDE_H
