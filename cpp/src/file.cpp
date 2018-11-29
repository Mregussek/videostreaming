//
// Created by mateusz on 27.11.18.
//

#include <fstream>
#include <string>
#include "file.h"


file::file()
: fileName("none")
{

}

file::file(std::string& name)
: fileName(name)
{

}

void file::writeToFile(unsigned char* data, int length)
{
    std::ofstream writeTo(this ->fileName);

    if(writeTo.is_open())
    {
        char toWrite[length];

        for(int i = 0; data[i] != '\0'; i++)
            toWrite[i] = data[i];

        writeTo.write(toWrite, length);
    }

    writeTo.close();
}

void file::readFromFile(int length)
{
    std::ifstream readFrom(this ->fileName);
    char received[length];

    if(readFrom.is_open())
        readFrom >> received;

    this ->receivedData = received;

    readFrom.close();
}
