#include <iostream>

// strcmp
#include <string.h>

void str_to_uint16(const char* str, uint16_t* res)
{
    char *end;
    errno = 0;
    long val = strtol(str, &end, 10);

    if (errno || end == str || *end != '\0' || val < 0 || val >= 0x10000)
        exit(5);

    *res = (uint16_t)val;
}

int main(int argc, char** argv)
{
    std::cout << "START\n";
    std::cout << "Number: " << argc << "\n";
    
    for(int i = 0; i < argc; i++)
        std::cout << i << " - " << argv[i] << "\n";

    if(strcmp(argv[3], "tcp") == 0)
        std::cout << "Done\n";
    else
        std::cout << "Try again\n";
    
    uint16_t* port = new uint16_t();

    str_to_uint16(argv[2], port);

    std::cout << *port << "\n";
    std::cout << *port + 10 << "\n";

    return 0;
}