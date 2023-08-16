//strc_ref.cpp -- using structure references
#include <iostream>
#include <string>
struct free_throws
{
    std::string name;
    int made;
    int attempts;
    float percent;
};

void display(const free_throws & ft);
void set_pc(free_throws & ft);
free_throws & accumulate(free_throws &target, const free_throws &source);

free_throws accumulate_test(free_throws & target);
free_throws & return_empty(free_throws & input);
const free_throws & clone(free_throws & ft);

int main()
{
    // [NOTICE] partial initialization, rest part is 0
    free_throws one = {"Ifelsa Branch", 13, 14};
    free_throws two = {"Andor Knott", 10, 16};
    free_throws three = {"Minnie Max", 7, 9};
    free_throws four = {"Whily Looper", 5, 9};
    free_throws five = {"Long Long", 6, 14};
    free_throws team = {"Throwgoods", 0, 0};
    free_throws dup;
    set_pc(one);
    display(one);
    accumulate(team, one);
    display(team);
// use return value as argument
    display(accumulate(team, two));
    accumulate(accumulate(team, three), four);
    display(team);
// use return value in assignment
    dup = accumulate(team,five);
    std::cout << "Displaying team:\n";
    display(team);
    std::cout << "Displaying dup after assignment:\n";
    display(dup);
    set_pc(four);
// ill-advised assignment
    // accumulate(dup,five) = four;
    accumulate_test(dup) = four; //[NOTICE] weird, compile should not pass, but it pass, textbook(p267) is wrong
    std::cout << "Displaying dup after ill-advised assignment:\n";
    display(dup);
    // std::cin.get();

    std::cout << "Extra Test" << std::endl;
// [NOTICE] return invalid reference. compile error.
    // free_throws test = return_empty(one);
    // display(test);

// [NOTICE] return function allocated variable.
    free_throws test2 = clone(one);

// [NOTICE] return const reference.
    // clone(one) = two; // [NOTICE] compile error, returned const reference is a unchangeable lvalue.

    display(test2);

    return 0;
}

void display(const free_throws & ft)
{
    using std::cout;
    cout << "Name: " << ft.name << '\n';
    cout << "  Made: " << ft.made << '\t';
    cout << "Attempts: " << ft.attempts << '\t';
    cout << "Percent: " << ft.percent << '\n';
}
void set_pc(free_throws & ft)
{
    if (ft.attempts != 0)
        ft.percent = 100.0f *float(ft.made)/float(ft.attempts);
    else
        ft.percent = 0;
}

free_throws & accumulate(free_throws & target, const free_throws & source)
{
    target.attempts += source.attempts;
    target.made += source.made;
    set_pc(target);
    return target; // [NOTICE] Return a reference.
}

free_throws accumulate_test(free_throws & target){
    free_throws copy_target = target;
    return copy_target;
    // return target;
}

free_throws & return_empty(free_throws & input){
    free_throws temp_target = input;
    // return temp_target; // [NOTICE] compile error.
    return input;
}

const free_throws & clone(free_throws & ft){
    free_throws * ft_ptr = new free_throws(ft);
    return *ft_ptr;

    //[NOTICE] textbook example(p268), Segmentation fault.
    // free_throws *pt;
    // *pt = ft;
    // return *pt;
}