#include "Menu.h"

Menu::Menu()
: Network(), Displayer()
{}

void Menu::menu()
{
    clearScreen();
    std::cout << "Current Settings" << std::endl;
    std::cout << "IP: " << getServerIp() << " Port: "<< getPort() << std::endl;
    std::cout << "1. Start watching" << std::endl;
    std::cout << "2. Configure" << std::endl;
    std::cout << "3. Usage" << std::endl;
    std::cout << "4. Exit" << std::endl;
    int choice;
    std::cout << "> ";
    std::cin >> choice;

    switch(choice)
    {
        case 1:
            startWatching();
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

void Menu::startWatching()
{
    std::cout << "Defining socket..." << std::endl;
    defSocket();
    std::cout << "Defining sockaddr..." << std::endl;
    defSockaddr();
    std::cout << "Connecting to " << getServerIp() << " " << getPort() << std::endl;
    connectToServer();

    checkIfContinuous();
    createWindow();

    uchar* metadata = getMetadata();

    while (getKey() != 'q')
    {
        receiveData(metadata, getImageSize());

        showImage();

        if (wait() >= 0)
            break;
    }

    delete metadata;
    closeConnection();
}

void Menu::configure()
{
    clearScreen();
    std::cout << "1. Change server ip (" << getServerIp() << ")" << std::endl;
    std::cout << "2. Change port (" << getPort() << ")" << std::endl;
    std::cout << "3. Back" << std::endl;

    int choice;

    while(true)
    {
        std::cout << "> ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                clearScreen();
                changeIp();
                break;
            case 2:
                clearScreen();
                changePort();
                break;
            case 3:
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
              << "Please remember to set correct ip and port!" << std::endl;

    sleep(5);
    menu();
}

void Menu::changeIp()
{
    clearScreen();
    std::string newIp;
    char choice;

    while(true)
    {
        clearScreen();
        std::cout << "Choose new ip: ";
        std::cin >> newIp;
        std::cout << "Is this ip correct?" << std::endl;
        std::cout << "[y/n] ";
        std::cin >> choice;

        if (choice == 'y' || choice == 'Y')
        {
            setServerIp(newIp);
            std::cout << "Changed successfully!" << std::endl;
            break;
        }
    }

    configure();
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

void Menu::clearScreen()
{
    if (system( "cls" ))
        system( "clear" );
}