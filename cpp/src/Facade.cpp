//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   1.05.2019

#include "Facade.h"

namespace mrz
{
    Facade::Facade(ServerStrategy* server)
    {
        run_server(server);
    }

    Facade::Facade(ClientStrategy* client)
    {
        run_client(client);
    }

    void Facade::run_server(ServerStrategy* server)
    {
        auto camera = new Camera();

        server ->define_socket();
        server ->create_server_then_listen();

        camera ->check_if_continuous();

        while(true)
        {
            camera ->got_frame = camera ->read_frame();

            if(!camera ->got_frame)
                break;

            camera ->process_image();

            server ->refresh_metadata(camera ->gray_image ->data);
            server ->sent_data = server ->send_data(camera ->get_image_size());

            if(!server ->sent_data)
                break;
        }

        server ->close_connection();
    }

    void Facade::run_client(ClientStrategy* client)
    {
        auto display = new Displayer();

        client ->define_socket();
        client ->connect_to_server();

        display ->check_if_continuous();

        client ->pair_metadata(display ->get_metadata());

        while (display ->get_key() != 'q')
        {
            client ->receive_data(display ->get_image_size());

            display ->show_image();

            if (display ->wait() >= 0)
                break;
        }

        delete display;
        client ->close_connection();
    }
}