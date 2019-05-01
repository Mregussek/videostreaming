//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   1.05.2019

#ifndef VIDEOSTREAMING_SERVERSTRATEGY_H
#define VIDEOSTREAMING_SERVERSTRATEGY_H

#include <errno.h>

namespace mrz
{
    class ServerStrategy
    {
    public:
        virtual void define_socket() {}
        virtual void create_server_then_listen() {}
        virtual void refresh_metadata(unsigned char*) {}
        virtual bool send_data(size_t&) { return true; }
        virtual void close_connection() {}
        virtual void char_to_uint16(const char *str, uint16_t *res)
        {
            char *end;
            errno = 0;
            long val = strtol(str, &end, 10);

            if (errno || end == str || *end != '\0' || val < 0 || val >= 0x10000)
                //handle_str_to_uint16();
                exit(10);

            *res = (uint16_t)val;
        }

        bool sent_data;
    };
}

#endif //VIDEOSTREAMING_SERVERSTRATEGY_H
