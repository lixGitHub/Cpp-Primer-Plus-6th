// secref.cpp -- defining and using a reference
#include <iostream>
int main()
{
    using namespace std;
    int rats = 101;
    int cats = 303;
    int & rodents = rats;   // rodents is a reference
    int & test_ref = rats; // third reference.
    int * const const_ptr = &rats; // [NOTICE] const pointer similar to reference.
    // int * const const_ptr2; // [NOTICE] error, const pointer need initialize.
    int * ptr;  // [NOTICE] normal pointer does not require initialization

    // int cont *  ==  const int *
    int const * test_ptr;
    test_ptr = &rats;
    test_ptr = &cats;
    // *test_ptr = 145;

     // [NOTICE] c_ptr can change, 
     const int * c_ptr;
     c_ptr = &rats;
     std::cout << "const int * c_ptr(rats) = " << *c_ptr << endl;
     c_ptr = &cats;
     std::cout << "const int * c_ptr(cats) = " << *c_ptr << endl;
     // *c_ptr = 104; //[NOTICE] *c_ptr cannot change

    cout << "rats = " << rats;
    cout << ", rodents = " << rodents 
         << ", test_ref = " << test_ref << endl;

    cout << "rats address = " << &rats;
    cout << ", rodents address = " << &rodents << endl;

    int bunnies = 50;
    rodents = bunnies;     // [NOTICE] can we change the reference? no
    *const_ptr = 79;       // [NOTICE] change through const pointer.
    // const_ptr = &bunnies;  // [NOTICE] unlike reference, this will be error.

    cout << "bunnies = " << bunnies;
    cout << ", rats = " << rats;
    cout << ", rodents = " << rodents 
         << ", test_ref = " << test_ref << endl;

    cout << "bunnies address = " << &bunnies;
    cout << ", rodents address = " << &rodents << endl;
    // cin.get();
    return 0; 
}
