//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   rzeczyca@student.agh.edu.pl
//   1.05.2019

#include "Facade.h"

namespace mrz
{
    void Facade::init_client_tcp(TCPclient* client)
    {
        auto display = new Displayer();

        client ->define_socket();
        client ->connect_to_server();

        display ->check_if_continuous();

        client ->pair_metadata( display ->get_metadata() );

        while(*(display ->key) != 'q')
        {
            client ->receive_data(display ->get_image_size());

            display ->show_image("TCP");

            if (display ->wait() >= 0)
                break;
        }

        delete display;
        client ->close_connection();
    }

    void Facade::init_server_tcp(TCPserver* server)
    {
        auto camera = new Camera();
        camera ->open_camera();

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

        delete camera;
        server ->close_connection();
    }

    void Facade::init_client_udp(UDPclient* client)
    {
        client ->define_socket();

        auto cam = new Camera;
        cam ->open_camera();
        std::cout << "Started sending packets!" << std::endl;
        int j = 0;

        while(j != 2000)
        {
            if(! cam ->read_frame() )
                continue;

            cam ->encode_image();

            int total_pack = 1 + (cam ->encoded.size() - 1) / *(client ->packet_size);

            client ->send_data(&total_pack, sizeof(int));

            for(int i = 0; i < total_pack; i++)
                client ->send_data(&cam ->encoded[i * *(client ->packet_size)], *(client ->packet_size));

            j++;
        }

        delete cam;
    }

    void Facade::init_server_udp(UDPserver* server)
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

            int* total_pack = new int( reinterpret_cast<int*>(buffer)[0] );
            char* long_buffer = new char[*(server ->max_recv_message) * *total_pack];

            for(int i = 0; i < *total_pack; i++)
            {
                server ->receive_data(buffer, *buffer_length);

                if( *(server ->recv_message) != *(server ->max_recv_message))
                {
                    std::cerr << "Received unexpected message" << std::endl;
                    continue;
                }

                memcpy(&long_buffer[i * *(server ->max_recv_message)],
                       buffer, *(server ->max_recv_message));
            }

            auto display = new Displayer(*total_pack, long_buffer);
            display ->decode_image();
            display ->show_image("UDP");

            delete [] long_buffer;

            *key = display ->wait();

            delete display;
            delete total_pack;
        }

        server ->close_connection();
        delete key;
    }
}
