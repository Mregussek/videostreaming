#include "Menu.h"

Menu::Menu()
: Network(), Camera()
{}

void Menu::menu()
{
    clearScreen();
    std::cout << "Current Settings" << std::endl;
    std::cout << "Port: " << getPort() << std::endl;
    std::cout << "1. Start streaming" << std::endl;
    std::cout << "2. Configure" << std::endl;
    std::cout << "3. Usage" << std::endl;
    std::cout << "4. Exit" << std::endl;
    int choice;
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
            menu();
            break;
    }
}

void Menu::startStreaming()
{
    std::cout << "1" << std::endl;
    defServerSocket();
    std::cout << "1" << std::endl;
    defSockaddr( getPort() );
    std::cout << "1" << std::endl;
    createServerAndListen();

    std::cout << "1" << std::endl;
    checkContinuous();
    acceptFirstConnection();

    while(true)
    {
        readFrame();
        proccessImage();

        sendData(grayImage, getImageSize());
    }
}

void Menu::configure()
{
    clearScreen();
    std::cout << "1. Change port (" << getPort() << ")" << std::endl;
    std::cout << "2. Back" << std::endl;

    int choice;

    while(true)
    {
        std::cout << "> ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                clearScreen();
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
    std::cout << "WAIT 5 SECONDS TO CONTINUE!" << std::endl << std::endl;
    std::cout << "Firstly you are supposed to run server,\n"
                 << "which is the app in \"rpi\" directory.\n"
                 << "Afterwards run client and that\'s it!\n"
                 << "Please remember to set correct port!" << std::endl;

    std::cout << "\nThankfully to socket package we can start\n"
              << "start server on every available interface.\n"
              << "In that case don\'t worry, you will be able\n"
              << "to connect!" << std::endl;
    sleep(5);
    menu();
}

void Menu::clearScreen()
{
    if (system( "cls" ))
        system( "clear" );
}

void Menu::changePort()
{
    clearScreen();
    uint16_t newPort;
    char choice;

    while(true)
    {
        clearScreen();
        std::cout << "Choose new port: ";
        std::cin >> newPort;
        std::cout << "Is this port correct?" << std::endl;
        std::cout << "[y/n] ";
        std::cin >> choice;

        if (choice == 'y' || choice == 'Y')
        {
            setPort(newPort);
            std::cout << "Changed successfully!" << std::endl;
            break;
        }
    }

    configure();
}