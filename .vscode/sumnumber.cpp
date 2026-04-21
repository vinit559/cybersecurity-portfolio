#include <iostream>
#include <complex> // Standard library for complex numbers

int main() {
    // Define complex numbers (real, imaginary)
    std::complex<double> z1(3.0, 4.0); 
    std::complex<double> z2(1.0, 2.0);

    // Perform arithmetic
    auto sum = z1 + z2;
    auto product = z1 * z2;

    std::cout << "z1: " << z1 << "\n";
    std::cout << "Sum: " << sum << "\n";
    std::cout << "Product: " << product << "\n";
    std::cout << "Magnitude of z1: " << std::abs(z1) << std::endl;

    return 0;
}
