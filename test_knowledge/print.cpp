#include <iostream>
#include <cstdint>

/*
When you try to output a uint8_t using std::cout, it's treated as a character rather than a numeric value. 
This is because uint8_t is often used to represent single bytes, which can correspond to ASCII characters.

Here's why this happens:
Type Interpretation:
std::cout interprets the data type of the variable you're trying to output. 
Since uint8_t is an unsigned 8-bit integer, it falls under the "character" category.

ASCII Conversion:
If the value stored in the uint8_t variable represents a valid ASCII character, std::cout will output that character.

Non-Printable Characters:
If the value doesn't correspond to a printable character, you might see nothing printed or unexpected behavior.

How to Fix:
To output the numeric value of a uint8_t variable, you can cast it to an integer type before printing:
*/
int main() {
    uint8_t value = 65; // ASCII value for 'A'

    std::cout << value << std::endl; // Outputs 'A'
    std::cout << static_cast<int>(value) << std::endl; // Outputs 65
}