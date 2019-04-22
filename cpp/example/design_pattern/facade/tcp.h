#include "client.h"

namespace mrz
{
    class TCP : public Client
    {
    public:
        TCP() {}

        void create_client() override;
        void connect() override;
        void send() override;
        void close() override;
    };

    void TCP::create_client()
    {
        std::cout << "TCP creates\n";
    }

    void TCP::connect()
    {
        std::cout << "TCP connects\n";
    }

    void TCP::send()
    {
        std::cout << "TCP sends\n";
    }
    
    void TCP::close()
    {
        std::cout << "TCP closes\n";
    }
}