#include <iostream>
#include "include/Complex.h"

int main() {
    Complex c1(10, 5), c2(2, 4);
    Complex c3 = c1 + c2; // addition
    std::cout << c3 << std::endl;

    // demonstrate other ops
    Complex csub = c1 - c2;
    Complex cmul = c1 * c2;
    std::cout << "sub: " << csub << std::endl;
    std::cout << "mul: " << cmul << std::endl;

    return 0;
}
