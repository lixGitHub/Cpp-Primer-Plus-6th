// inline.cpp -- using an inline function
#include <iostream>

// an inline function definition
inline double square_inline(double x) { return x * x; }

// add macro to compare.
#define square_macro(x) x*x

// [NOTICE] test inline function cannot be recursive
inline int fibonacci(int x){
    if(x==1) {return x;}
    else {return x*fibonacci(x-1);} 
}

int main()
{
    using namespace std;
    // double a, b;
    double c = 13.0;

    double a_in = square_inline(5.0);
    double a_ma = square_macro(5.0);
    std::cout << "square(5):            a_in = " << a_in << ", a_ma = " << a_ma << std::endl;
    double b_in = square_inline(4.5 + 7.5);   // can pass expressions
    double b_ma = square_macro(4.5 + 7.5);
    std::cout << "square(4.5+7.5):      b_in = " << b_in << ", b_ma = " << b_ma << std::endl;
    double c_in = square_inline(c++);
    c = 13.0;
    double c_ma = square_macro(c++);
    std::cout << "square(c++) c==13:    c_in = " << c_in << ", c_ma = " << c_ma << std::endl;

    double a = square_inline(5.0);
    double b = square_inline(4.5 + 7.5);   // can pass expressions

    cout << "a = " << a << ", b = " << b << "\n";
    cout << "c = " << c;
    cout << ", c squared = " << square_inline(c++) << "\n";
    cout << "Now c = " << c << "\n";
    // cin.get();

    int d = 5;
    cout << d << " factorial = " << fibonacci(d) << endl;
    return 0;  
}
