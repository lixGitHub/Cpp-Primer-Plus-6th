#include <iostream>
#include <stdexcept>

void myFunction() {
    throw std::runtime_error("An error occurred!");
    std::cout << "This line will not be executed." << std::endl;
}

int main() {
    try {
        myFunction();
    } catch (const std::runtime_error& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
    return 0;
}