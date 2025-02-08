// C++ Program to Handle SIGABRT Signal in C++
#include <csignal>
#include <cstdlib>
#include <iostream>
// using namespace std;

// Signal handler function for SIGABRT
void HandleSignal(int signal)
{
    if (signal == SIGABRT)
    {
        std::cerr << "SIGABRT received. Terminating the Program...\n";

        // Perform any cleanup tasks here
        // optionally holding the program
        int i;
        std::cin >> i;
        exit(1);
    }
    else if (signal == SIGSEGV)
    {
        std::cerr << "SIGSEGV received. Terminating the Program.\n";
        exit(1);
    }
}

void SegmentFault()
{
    int* ptr = nullptr;
    *ptr = 1;
}

int main()
{
    signal(SIGSEGV, HandleSignal);

    // Set up the signal handler for SIGABRT
    signal(SIGABRT, HandleSignal);

    // Inform the user that the program is running
    std::cout << "Program running. Send SIGABRT signal to "
            "terminate.\n";

    // // send the SIGABRT signal by calling the abort function
    // abort();

    // Cause segment fault.
    SegmentFault();

    // The below code will not be executed
    std::cout << "This line will not be printed";

    return 0;
}
