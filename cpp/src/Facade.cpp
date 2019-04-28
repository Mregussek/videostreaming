//
// Created by mateusz on 22.04.19.
//

#include "Facade.h"

namespace mrz
{
    Facade::Facade(ClientStrategy* c)
    : client(c), test(0)
    {
        run_client();
    }

    Facade::Facade(ServerStrategy* s)
    : server(s), test(0)
    {
        run_server();
    }

    void Facade::run_client()
    {
        std::cout << test++ << "\n"; // 0
        client ->create_socket();
        std::cout << test++ << "\n"; // 1
        client ->connect_to_server();

        std::cout << test++ << "\n"; // 2
        display = new Displayer();
        std::cout << test++ << "\n"; // 3
        display ->if_continuous();

        std::cout << test++ << "\n"; // 4
        client ->recv_data = display ->get_metadata();
        std::cout << test++ << "\n"; // 5
        client ->recv_data_size = display ->image_size;
        
        while(*(display ->key) != 'q')
        {
            std::cout << test++ << "\n"; // 6...
            client ->receive_data();
            std::cout << test++ << "\n"; //7...
            display ->show_image();
            
            if(display ->wait() >= 0)
                break;
        }
        
        client ->close_connection();
    }

    void Facade::run_server()
    {
        std::cout << test++ << "\n"; // 0
        server ->create_socket();
        std::cout << test++ << "\n"; // 1
        server ->create_server();

        std::cout << test++ << "\n"; // 2
        cam = new Camera();
        std::cout << test++ << "\n"; // 3
        cam ->if_continuous();

        std::cout << test++ << "\n"; // 4
        server ->data_to_send = cam ->get_metadata();
        std::cout << test++ << "\n"; // 5
        server ->data_to_send_size = cam ->image_size;
        
        while(true)
        {
            std::cout << test++ << "\n"; // 6...
            cam ->read_frame();
            std::cout << test++ << "\n"; // 7...
            cam ->process_frame();

            std::cout << test++ << "\n"; // 8...
            server ->send_data();
        }
        
        server ->close_connection();
    }
}