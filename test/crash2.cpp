#include <iostream>
#include <signal.h>
#include <execinfo.h>
#include <unistd.h>

void handle_segfault(int sig)
{
    void *array[10];
    size_t size;

    // get void*'s for all entries on the stack
    size = backtrace(array, 10);

    // print out all the frames to stderr
    fprintf(stderr, "Error: signal %d:\n", sig);
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    exit(1);
}

void SegmentFault()
{
    int *p = nullptr;
    *p = 10; // This will cause a segmentation fault
}

int main()
{
    signal(SIGSEGV, handle_segfault);

    // int *p = nullptr;
    // *p = 10; // This will cause a segmentation fault
    SegmentFault();

    return 0;
}