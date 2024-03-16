#include "InfInt.h" // For handling large integers
#include <iostream>

InfInt karatsuba(const InfInt& x, const InfInt& y) {
    // Base case for the recursion
    if (x < 10 || y < 10) {
        return x * y;
    }

    // Calculate the size of the numbers
    size_t size = std::max(x.numberOfDigits(), y.numberOfDigits());
    size_t halfSize = size / 2;

    // Split the digit sequences in the middle
    InfInt high1 = x / InfInt("1" + std::string(halfSize, '0')); // equivalent to x / 10^halfSize
    InfInt low1 = x % InfInt("1" + std::string(halfSize, '0')); // equivalent to x % 10^halfSize
    InfInt high2 = y / InfInt("1" + std::string(halfSize, '0')); // y / 10^halfSize
    InfInt low2 = y % InfInt("1" + std::string(halfSize, '0')); // y % 10^halfSize

    // Recursively calculate three products
    InfInt z0 = karatsuba(low1, low2);
    InfInt z1 = karatsuba((low1 + high1), (low2 + high2));
    InfInt z2 = karatsuba(high1, high2);

    // The final product, based on the three above
    return z2 * InfInt("1" + std::string(2 * halfSize, '0')) + (z1 - z2 - z0) * InfInt("1" + std::string(halfSize, '0')) + z0;
}

int main() {
    InfInt x = "12345678901234567890";
    InfInt y = "98765432109876543210";

    InfInt result = karatsuba(x, y);
    std::cout << "The result of " << x << " * " << y << " is " << result << std::endl;

    return 0;
}