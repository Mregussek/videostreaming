//   Written by Mateusz Rzeczyca.
//   Student - AGH University of Science and Technology
//   info@mateuszrzeczyca.pl
//   30.03.2019

//#define CLI
#define SER

#ifdef CLI
#include "src/client.h"
mrz::CLIENT object;
#endif

#ifdef SER
#include "src/server.h"
mrz::SERVER object;
#endif

int main()
{
    object.menu();
    return 0;
}