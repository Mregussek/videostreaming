#include <iostream>

namespace mrz
{
    class Client
    {
    public:
        virtual void create_client() = 0;
        virtual void connect() = 0;
        virtual void send() = 0;
        virtual void close() = 0;
    };
}