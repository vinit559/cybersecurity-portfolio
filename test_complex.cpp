#include <iostream>
#include <cassert>
#include "include/Complex.h"

int main() {
    Complex a(3, 2);
    Complex b(1, 4);

    // addition
    Complex sum = a + b;
    assert(sum.real == 4 && sum.imag == 6);

    // subtraction
    Complex diff = a - b;
    assert(diff.real == 2 && diff.imag == -2);

    // multiplication
    Complex prod = a * b; // (3+2i)*(1+4i) = 3 + 12i + 2i + 8i^2 = (3-8) + 14i = -5 + 14i
    assert(prod.real == -5 && prod.imag == 14);

    // stream output basic check (just ensure it doesn't crash)
    std::cout << "sum: " << sum << std::endl;
    std::cout << "diff: " << diff << std::endl;
    std::cout << "prod: " << prod << std::endl;

    std::cout << "All tests passed" << std::endl;
    return 0;
}
