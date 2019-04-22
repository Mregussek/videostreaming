//
// Created by mateusz on 22.04.19.
//

#include "Facade.h"

namespace mrz
{
    Facade::Facade(ClientStrategy* c)
    : client(c)
    {
        run_client();
    }

    Facade::Facade(ServerStrategy* s)
    : server(s)
    {
        run_server();
    }

    void Facade::run_client()
    {
        client ->create_socket();
        client ->connect_to_server();


    }

    void Facade::run_server()
    {

    }
}