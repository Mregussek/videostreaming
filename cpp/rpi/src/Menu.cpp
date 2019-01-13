#include "Menu.h"

void Menu::menu()
{
    clearScreen();
    std::cout << "1. Start streaming" << std::endl;
    std::cout << "2. Configure" << std::endl;
    std::cout << "3. Usage" << std::endl;
    std::cout << "4. Exit" << std::endl;
    int choice;

    while(true)
    {
        std::cout << "> ";
        std::cin >> choice;

        switch(choice)
        {
            case 1:
                startStreaming();
                break;
            case 2:
                configure();
                break;
            case 3:
                usage();
                break;
            case 4:
                exit(1);
            default:
                continue;
        }
    }
}

void Menu::startStreaming()
{
    Network server = Network();
    server.defServerSocket();
    server.defSockaddr();
    server.createServerAndListen();

    Camera camera = Camera();
    camera.checkContinuous();
    server.acceptFirstConnection();

    while(true)
    {
        camera.readFrame();
        camera.proccessImage();

        server.sendData(camera.grayImage, camera.getImageSize());
    }
}

void Menu::configure()
{
    std::cout << "1. Change port" << std::endl;
    std::cout << "2. Back" << std::endl;

    int choice;

    while(true)
    {
        std::cout << "> ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                changePort();
                break;
            case 2:
                menu();
                break;
            default:
                continue;
        }
    }
}

void Menu::usage()
{
    clearScreen();
    std::cout << "PLEASE PRESS ENTER TO BACK TO THE MENU!" << std::endl << std::endl;
    std::cout << "Firstly you are supposed to run server,\n"
                 << "which is the app in \"rpi\" directory.\n"
                 << "Afterwards run client and that\'s it!\n"
                 << "Please remember to set correct values!" << std::endl;

    int a;
    std::cin >> a;
    menu();
}

void Menu::clearScreen()
{
    if (system( "cls" ))
        system( "clear" );
}

void Menu::changePort()
{

}