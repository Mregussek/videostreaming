#include "udp.h"

namespace mrz
{
    class Facade 
    {
    public:
        Facade() {}

        Facade(int protocol)
        {
            switch(protocol)
            {
                case 1:
                    this ->client = reinterpret_cast<Client*>( new TCP() );
                    break;
                case 2:
                    this ->client = reinterpret_cast<Client*>( new UDP() );
                    break;
                default:
                    // handle bad protocol choice
                    return;
            }
        }

        Facade(TCP* tcp)
        {
            this ->client = reinterpret_cast<Client*>(tcp);
        }

        Facade(UDP* udp)
        {
            this ->client = reinterpret_cast<Client*>(udp);
        }

        ~Facade()
        {
            delete client;
        }

        void create() { client ->create_client(); }
        void send() { client ->send(); }
        void connect() { client ->connect(); }
        void close() { client ->close(); }

    private:
        Client* client;
    };
}