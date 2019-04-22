#include "facade.h"

int main()
{
    mrz::Facade* connection = new mrz::Facade(1);

    connection ->create();
    connection ->close();

    delete connection;

    mrz::Facade* connection_2 = new mrz::Facade(2);

    connection_2 ->create();
    connection_2 ->close();

    delete connection_2;

    mrz::TCP* tcp = new mrz::TCP();
    mrz::Facade* prot = new mrz::Facade(tcp);

    prot ->send();
    prot ->close();

    delete prot;
    delete tcp;

    mrz::UDP* udp = new mrz::UDP();
    mrz::Facade* prot_2 = new mrz::Facade(udp);
    
    prot_2 ->connect();
    prot_2 ->send();

    delete prot_2;
    delete udp;

    return 0;    
}