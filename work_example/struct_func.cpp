#include <iostream>


struct delete_func{
    constexpr void operator()(int * int_ptr){
        // std::cout << "delete the memory\n";
        delete int_ptr;
    }
};

void print_null(int * ptr)
{
    if (ptr == nullptr)
    {
        std::cout << "is null ptr.\n";
    }
    else
    {
        std::cout << "is valid ptr." << "its value: " << *ptr << "\n";
    }
}


int main(int argc, char *argv[])
{
    int * ptr = new int(50);
    print_null(ptr);
    delete_func struct_func;
    struct_func(ptr);
    print_null(ptr);
}