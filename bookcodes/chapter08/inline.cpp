// inline.cpp -- using an inline function
#include <iostream>

// an inline function definition
inline double square(double x) { return x * x; }

// add macro to compare.
// #define square(x) x*x

// test inline function cannot be recursive
inline int fibonacci(int x){
    if(x==1) {return x;}
    else {return x*fibonacci(x-1);} 
}

int main()
{
    using namespace std;
    double a, b;
    double c = 13.0;

    a = square(5.0);
    b = square(4.5 + 7.5);   // can pass expressions
    cout << "a = " << a << ", b = " << b << "\n";
    cout << "c = " << c;
    cout << ", c squared = " << square(c++) << "\n";
    cout << "Now c = " << c << "\n";
    // cin.get();

    int d = 5;
    cout << d << " factorial = " << fibonacci(d) << endl;
    return 0;  
}
