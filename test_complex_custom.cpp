#include "include/Complex.h"
#include "tests/test_runner.h"
#include <cmath>

int main() {
    TestRunner tr;
    const double eps = 1e-9;

    // Basic ops
    Complex a(3,2), b(1,4);
    Complex sum = a + b;
    tr.expectTrue(sum.real==4 && sum.imag==6, "Addition");

    Complex diff = a - b;
    tr.expectTrue(diff.real==2 && diff.imag==-2, "Subtraction");

    Complex prod = a * b; // -5 + 14i
    tr.expectTrue(prod.real==-5 && prod.imag==14, "Multiplication");

    // division by scalar
    Complex s = prod / 1.0;
    tr.expectTrue(s == prod, "Division by scalar");

    // conjugate & magnitude
    Complex c(3,4);
    tr.expectTrue(c.conjugate().imag == -4, "Conjugate");
    tr.expectTrue(std::fabs(c.magnitude()-5.0) < eps, "Magnitude");

    // approxEquals
    Complex x(0.30000000000000004, 0.2); // floating rounding
    Complex y(0.3, 0.2);
    tr.expectTrue(x.approxEquals(y, 1e-12), "ApproxEquals");

    // compound assignment
    Complex u(1,1);
    u += Complex(2,3); // becomes 3 + 4i
    tr.expectTrue(u == Complex(3,4), "Compound +=");

    // division by zero check (should throw)
    bool threw = false;
    try { Complex z = a / Complex(0,0); } catch(...) { threw = true; }
    tr.expectTrue(threw, "Division by zero throws");

    return tr.report();
}
