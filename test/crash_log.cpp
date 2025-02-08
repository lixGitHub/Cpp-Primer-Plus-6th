#include <cstdio>
#include <csignal>
#include <iostream>
#include <unistd.h>

// Function to simulate a crash by dereferencing a null pointer
void crash_handler(int signum) {
    std::cerr << "Crash detected! Signal: " << signum << std::endl;
    // Trigger a crash
    int* ptr = nullptr;
    *ptr = 42; // Dereference a null pointer, causing a segmentation fault
}

int main() {
    // Set up a signal handler for segmentation fault (SIGSEGV)
    std::signal(SIGSEGV, crash_handler);

    // Open a log file for writing
    FILE* logFile = fopen("logfile.txt", "w");
    if (logFile == nullptr) {
        std::cerr << "Failed to open log file!" << std::endl;
        return 1;
    }

    // Simulate a normal log write
    fprintf(logFile, "Writing this log to the file...\n");

    // Simulate a crash (e.g., in the middle of writing to the log file)
    std::cout << "Simulating crash now..." << std::endl;
    raise(SIGSEGV); // Send a SIGSEGV signal to trigger the crash

    // This part will not be executed, but if it were, it would fail to write due to crash
    fprintf(logFile, "This will not be written.\n");

    fclose(logFile);
    return 0;
}
