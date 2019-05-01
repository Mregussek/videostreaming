#include <string.h>

namespace mrz
{
    class Second
    {
    public:
        Second() :
        struct_pointer( new Pointer() )
        { }

        ~Second()
        {
            delete pointer;
        }

        struct Pointer
        {
            Pointer()
            {
                value = new char();
                strcpy(value, "VALUE");
            }

            char* value;
        };

        int* pointer;
        Pointer* struct_pointer;

        int* get_pointer()
        {
            return pointer;
        }

        char* get_struct_pointer_value()
        {
            return struct_pointer ->value;
        }

        void do_sth()
        {
            (*pointer)++;
        }
    };
}