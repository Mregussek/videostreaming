//
// Created by mateusz on 22.11.18.
//

#include <iostream>
#include "network.h"

void menu();
void streaming();
void watching();

int main()
{
    menu();
}

void menu()
{
    begin:
    system("clear");

    std::cout << "1. Connect" << std::endl;
    std::cout << "2. Bind server" << std::endl;
    std::cout << "3. Exit";
    std::cout << "Please type correct number!" << std::endl;
    std::cout << "Choice:";

    int choice;
    std::cin >> choice;

    switch(choice)
    {
        case 1:
            watching();
            break;
        case 2:
            streaming();
            break;
        default:
            goto begin;
    }
}

void streaming()
{
    std::unique_ptr<network> streamVideo =
            std::make_unique<network>(7123, "10.42.0.30", "tcp");

    streamVideo ->createSocket();
    streamVideo ->bindServer( streamVideo ->serverAddress );
    streamVideo ->listenForConnection();
    streamVideo ->acceptCall( streamVideo ->clientAddress );

    // now should start streaming



    streamVideo ->closeConnection();
}

void watching()
{
    std::unique_ptr<network> watchVideo =
            std::make_unique<network>(7123, "10.42.0.30", "tcp");

    watchVideo ->createSocket();
    watchVideo ->connectServer();

    // now we should be allowed to see stream



    watchVideo ->closeConnection();
}
