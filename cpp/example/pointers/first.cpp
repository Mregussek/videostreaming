#include <iostream>

namespace mrz
{
    class First
    {
    public:
        First() :
        pointer( new int(5) )
        {}

        ~First()
        {
            delete pointer;
        }

        void pair_pointers(int* a, int* b)
        {
            std::cout << "Im inside method\n";
            a = b;
        }

        int* get_pointer()
        {
            return pointer;
        }

        int* pointer;
        char* char_pointer;
    };
}