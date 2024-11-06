// 
#include <iostream>

int main()
{
    int val1 = 5;
    int val2 = 18;

    // [pointed value is const]
    const int * const_int_ptr = &val1;
    // *const_int_ptr = 6; // [ERROR] the pointed value cannot be changed through this way.
    const_int_ptr = &val2; // [OK] the pointer can be changed.

    // [const int * == int const *]
    int const * int_const_ptr = &val1;
    // *int_const_ptr = 0; // [ERROR]
    int_const_ptr = &val2; // [OK]

    // [pointer is const]
    // int * const int_ptr_const; // [ERROR] need initialize.
    int * const int_ptr_const = &val1; // [OK]
    // int_ptr_const = &val2 // [ERROR] pointer cannot be changed.

    std::cout << val1 << ", "
              << *const_int_ptr << ", "
              << *int_const_ptr << ", "
              << *int_ptr_const << ", "
              << std::endl;

    return 0;
}
