//
// Created by mateusz on 27.11.18.
//

#ifndef VIDEOSTREAM_FILE_H
#define VIDEOSTREAM_FILE_H

#include <string>
#include "main.h"

class file {
public:
    file();
    explicit file(std::string&);

    void writeToFile(unsigned char*, int);
    void readFromFile(int);

private:
    std::string fileName;
    char* receivedData;
};


#endif //VIDEOSTREAM_FILE_H
