//filefunc.cpp -- function with ostream & parameter
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

class Student
{
private:
    /* data */
public:
    Student(/* args */);
    ~Student();
    virtual void printinfo() = 0;
};

Student::Student(/* args */)
{
}

Student::~Student()
{
}

class Undergraduate : public Student
{
private:
    /* data */
public:
    Undergraduate(/* args */);
    ~Undergraduate();
    virtual void printinfo(){
        std::cout << "This is Undergraduate\n";
    }
};

Undergraduate::Undergraduate(/* args */)
{
}

Undergraduate::~Undergraduate()
{
}


class Graduate : public Student
{
private:
    /* data */
public:
    Graduate(/* args */);
    ~Graduate();
    virtual void printinfo(){
        std::cout << "This is Graduate\n";
    }
};

Graduate::Graduate(/* args */)
{
}

Graduate::~Graduate()
{
}


void class_print(Student & stu){
    stu.printinfo();
}


void file_it(ostream & os, double fo, const double fe[],int n);
const int LIMIT = 5;
int main()
{
    ofstream fout;
    const char * fn = "ep-data.txt";
    fout.open(fn);
    if (!fout.is_open())
    {
        cout << "Can't open " << fn << ". Bye.\n";
        exit(EXIT_FAILURE); // [NOTICE] exit with 1, can check with echo $? 
    }
    double objective;
    cout << "Enter the focal length of your "
            "telescope objective in mm: ";
    cin >> objective;
    double eps[LIMIT];
    cout << "Enter the focal lengths, in mm, of " << LIMIT
         << " eyepieces:\n";
    for (int i = 0; i < LIMIT; i++)
    {
        cout << "Eyepiece #" << i + 1 << ": ";
        cin >> eps[i];
    }
    file_it(fout, objective, eps, LIMIT);
    file_it(cout, objective, eps, LIMIT);
    cout << "Done\n";
    // cin.get();
    // cin.get();

    // my test
    Undergraduate s1;
    Graduate s2;
    class_print(s1);
    class_print(s2);

    return 0;
}

void file_it(ostream & os, double fo, const double fe[],int n)
{
    // save initial formatting state
    ios_base::fmtflags initial;
    initial = os.setf(ios_base::fixed, ios_base::floatfield);
    std::streamsize sz = os.precision(0);
    os << "Focal length of objective: " << fo << " mm\n";
    os.precision(1);
    os.width(12);
    os << "f.l. eyepiece";
    os.width(15);
    os << "magnification" << endl;
    for (int i = 0; i < n; i++)
    {
        os.width(12);
        os << fe[i];
        os.width(15);
        os << int (fo/fe[i] + 0.5) << endl;
    }
    // restore initial formatting state
    os.setf(initial, ios_base::floatfield);
    os.precision(sz);
}
