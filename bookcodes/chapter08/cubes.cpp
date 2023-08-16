// cubes.cpp -- regular and reference arguments
#include <iostream>
#include <cmath>

double cube(double a);
double refcube(double &ra);
double refcube2(const double &ra);


int main ()
{
    using namespace std;
    double x = 3.0;

    cout << cube(x);
    cout << " = cube of " << x << endl;
    cout << refcube(x);
    cout << " = refcube of " << x << endl;

    // [NOTICE] compile error.
    x = 3;
    // cout << refcube(x + 3);
    // cout << " = refcube of " << x+3 << endl;

    // [NOTICE] generate temporary variable 
    x = 3;
    cout << refcube2(x+3)
         << " = refcube of " << x+3 << endl;
    long y = 10;
    cout << refcube2(y)
         << " = refcube of " << y << endl;
    cout << refcube2(5+3)
         << " = refcube of 5+3. " << endl;

    
    // [NOTICE] rvalue reference
    double a =  4;
    double && rrefa = a+3-8;
    double && rrefa2 = std::sqrt(a);
    cout << "a+3-8 = " << rrefa << endl;
    cout << "sqrt(a) = " << rrefa2 << endl;

    // cin.get();
    return 0;
}

double cube(double a)
{
    a *= a * a;
    return a;
}

// double refcube(const double &ra) // [NOTICE] compile error
double refcube(double &ra)
{
    ra *= ra * ra;
    return ra; 
}

double refcube2(const double &ra)
{
    return ra * ra * ra; 
}