// 
#include <iostream>

int main()
{
    int a = 5;
    int b = 18;

    std::cout << a << ", "
              << b << ", "
              << std::endl;
    
    // [ONLY works for int]
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;

    std::cout << a << ", "
              << b << ", "
              << std::endl;

    // [works for other type number]
    a = a + b;
    b = a - b;
    a = a - b;

    std::cout << a << ", "
              << b << ", "
              << std::endl;

    return 0;
}
