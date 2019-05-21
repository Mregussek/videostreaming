//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   1.05.2019

#include "Facade.h"

namespace mrz
{
    Facade::Facade(TCPserver* server)
    {
        run_server_tcp(server);
    }

    Facade::Facade(TCPclient* client)
    {
        run_client_tcp(client);
    }

    Facade::Facade(UDPserver* server)
    {
        run_server_udp(server);
    }

    Facade::Facade(UDPclient* client)
    {
        run_client_udp(client);
    }

    void Facade::run_server_tcp(TCPserver* server)
    {
        auto camera = new Camera();

        server ->define_socket();
        server ->create_server_then_listen();
        camera ->check_if_continuous();

        while(true)
        {
            if(! camera ->read_frame() )
                break;

            camera ->process_image();

            server ->refresh_metadata(camera ->gray_image ->data);

            if(! server ->send_data(camera ->get_image_size()) )
                break;
        }

        server ->close_connection();
    }

    void Facade::run_client_tcp(TCPclient* client)
    {
        auto display = new Displayer();

        client ->define_socket();
        client ->connect_to_server();

        display ->check_if_continuous();

        client ->pair_metadata( display ->get_metadata() );

        while(*(display ->key) != 'q')
        {
            client ->receive_data(display ->get_image_size());

            display ->show_image();

            if (display ->wait() >= 0)
                break;
        }

        delete display;
        client ->close_connection();
    }

    void Facade::run_client_udp(UDPclient* client)
    {
        client ->define_socket();

        auto cam = new Camera;

        while(*(cam ->key) != 'q')
        {
            if(! cam ->read_frame() )
                continue;

            cam ->encode_image();

            int* total_pack = new int(cam ->encoded.capacity() / *(client ->packet_size));

            client ->send_data(total_pack, sizeof(int));

            for(int i = 0; i < *total_pack; i++)
                client ->send_data(&cam ->encoded[i * *(client ->packet_size)], *(client ->packet_size));

            delete total_pack;

            cam ->wait();
        }
    }

    void Facade::run_server_udp(UDPserver* server)
    {
        server ->define_socket();
        server ->create_server_then_listen();

        int* buffer_length = new int(65540);
        char buffer[*buffer_length];
        int* key = new int;

        while(*key != 'q')
        {
            do
            {
                server ->receive_data(buffer, *buffer_length);
            } while( *(server ->recv_message) > sizeof(int));

            int total_pack = ((int*) buffer)[0];
            char* long_buffer = new char[*(server ->max_recv_message) * total_pack];

            for(int i = 0; i < total_pack; i++)
            {
                server ->receive_data(buffer, *buffer_length);

                if( *(server ->recv_message) != *(server ->max_recv_message))
                    continue;

                memcpy(&long_buffer[i * *(server ->max_recv_message)],
                       buffer, *(server ->max_recv_message));
            }

            auto display = new Displayer(total_pack, long_buffer);
            display ->decode_image();
            display ->show_image();

            delete [] long_buffer;

            *key = display ->wait();

            delete display;
        }

        server ->close_connection();
        delete key;
    }
}
