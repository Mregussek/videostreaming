// Want to proof that by assigning pointers 
// they have the same address and value
// In original project I had problems with this

#include "first.cpp"
#include "second.cpp"
#include "third.cpp"

int main()
{
    using mrz::First;
    using mrz::Second;
    using mrz::Third;

    First* first = new First();

    std::cout << "First Address: " << first << "\n";

    Second* second = new Second();

    std::cout << "Second Address: " << second << "\n";

    Third* third = new Third();

    std::cout << "Third Address: " << third << "\n";

    std::cout << "First Pointer Value: " << *(first ->pointer) << "\n";
    std::cout << "First Pointer Address: " << first ->pointer << "\n";

    second ->pointer = first ->pointer;
    third ->pointer = second ->pointer;

    std::cout << "Second Pointer Value: " << *(second ->pointer) << "\n";
    std::cout << "Second Pointer Address: " << second ->pointer << "\n";

    std::cout << "Third Pointer Value: " << *(third ->pointer) << "\n";
    std::cout << "Third Pointer Address: " << third ->pointer << "\n";

    first ->~First();

    std::cout << "AFTER DESTRUCTOR\n";
    std::cout << "Third Pointer Value: " << *(third ->pointer) << "\n";
    std::cout << "Third Pointer Address: " << third ->pointer << "\n";

    delete first;

    std::cout << "AFTER DELETE FIRST\n";
    std::cout << "Third Pointer Value: " << *(third ->pointer) << "\n";
    std::cout << "Third Pointer Address: " << third ->pointer << "\n";

    delete second;
    delete third;

    std::cout << "-------------------\n";

    std::cout << "Initializing ";
    First* f = new First();
    std::cout << " is";
    Second* s = new Second();
    std::cout << " hopefully";
    Third* t = new Third();
    std::cout << " done\n";

    s ->pointer = f ->get_pointer();
    std::cout << "Im here\n";
    f ->pair_pointers(t ->get_pointer(), s ->pointer);
    std::cout << "and at the end\n";

    std::cout << "First Pointer Value: " << *(f ->pointer) << "\n";
    std::cout << "First Pointer Address: " << f ->pointer << "\n";

    s ->do_sth();
    std::cout << "Second Pointer Value: " << *(s ->pointer) << "\n";
    std::cout << "Second Pointer Address: " << s ->pointer << "\n";

    // This will break!
    //std::cout << "Third Pointer Value: " << *(t ->pointer) << "\n";
    //std::cout << "Third Pointer Address: " << t ->pointer << "\n";

    //f ->char_pointer = s ->get_struct_pointer_value();
    f ->char_pointer = s ->struct_pointer ->value;
    std::cout << "Char Pointer: " << f ->char_pointer << "\n";

    return 0;
}