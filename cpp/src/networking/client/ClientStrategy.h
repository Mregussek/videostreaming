//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   1.05.2019

#ifndef VIDEOSTREAMING_CLIENTSTRATEGY_H
#define VIDEOSTREAMING_CLIENTSTRATEGY_H

namespace mrz
{
    class ClientStrategy
    {
    public:
        virtual void define_socket() {}
        virtual void connect_to_server() {}
        virtual void receive_data(unsigned char*, size_t&) {}
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
    };
}

#endif //VIDEOSTREAMING_CLIENTSTRATEGY_H
