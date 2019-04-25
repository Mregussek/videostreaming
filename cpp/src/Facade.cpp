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

        display = new Displayer();
        display ->if_continuous();
        
        client ->recv_data = display ->image_metadata;
        client ->recv_data_size = display ->image_size;
        
        while(*(display ->key) != 'q')
        {
            client ->receive_data();
            display ->show_image();
            
            if(display ->wait() >= 0)
                break;
        }
        
        client ->close_connection();
    }

    void Facade::run_server()
    {
        server ->create_socket();
        server ->create_server();
        
        cam = new Camera();
        cam ->if_continuous();
        
        server ->data_to_send = cam ->image_metadata;
        server ->data_to_send_size = cam ->image_size;
        
        while(true)
        {
            cam ->read_frame();
            cam ->process_frame();
            
            server ->send_data();
        }
        
        server ->close_connection();
    }
}