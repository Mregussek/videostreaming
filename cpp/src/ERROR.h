//
// Created by mateusz on 22.03.19.
//

#ifndef VIDEOSTREAMING_ERROR_H
#define VIDEOSTREAMING_ERROR_H

namespace mrz
{
    class Error
    {
    public:
        static void error_creating_socket() {}
        static void error_bind_server() {}
        static void error_accept_connection() {}
        static void error_sending_data() {}
        static void error_connecting_to_server() {}
    };
}

#endif //VIDEOSTREAMING_ERROR_H
