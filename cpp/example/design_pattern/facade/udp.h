#include "tcp.h"

namespace mrz
{
    class UDP : public Client
    {
    public:
        UDP() {}

        void create_client() override;
        void connect() override;
        void send() override;
        void close() override;
    };

    void UDP::create_client()
    {
        std::cout << "UDP creates\n";
    }

    void UDP::connect()
    {
        std::cout << "UDP connects\n";
    }

    void UDP::send()
    {
        std::cout << "UDP sends\n";
    }
    
    void UDP::close()
    {
        std::cout << "UDP closes\n";
    }
}