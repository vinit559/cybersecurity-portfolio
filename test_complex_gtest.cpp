#include "include/Complex.h"
#include <gtest/gtest.h>

TEST(ComplexTest, BasicOperations) {
    Complex a(3, 2);
    Complex b(1, 4);

    Complex sum = a + b;
    EXPECT_NEAR(sum.real, 4.0, 1e-9);
    EXPECT_NEAR(sum.imag, 6.0, 1e-9);

    Complex diff = a - b;
    EXPECT_NEAR(diff.real, 2.0, 1e-9);
    EXPECT_NEAR(diff.imag, -2.0, 1e-9);

    Complex prod = a * b; // -5 + 14i
    EXPECT_NEAR(prod.real, -5.0, 1e-9);
    EXPECT_NEAR(prod.imag, 14.0, 1e-9);

    Complex quot = prod / Complex(1, 0);
    EXPECT_NEAR(quot.real, -5.0, 1e-9);
    EXPECT_NEAR(quot.imag, 14.0, 1e-9);
}

TEST(ComplexTest, DivisionByZero) {
    Complex a(1,2);
    Complex zero(0,0);
    EXPECT_THROW(a / zero, std::runtime_error);
}

TEST(ComplexTest, ConjugateAndMagnitude) {
    Complex a(3,4);
    auto conj = a.conjugate();
    EXPECT_DOUBLE_EQ(conj.real, 3);
    EXPECT_DOUBLE_EQ(conj.imag, -4);
    EXPECT_DOUBLE_EQ(a.magnitude2(), 25);
    EXPECT_DOUBLE_EQ(a.magnitude(), 5);
}

TEST(ComplexTest, Equality) {
    Complex a(2,2);
    Complex b(2,2);
    Complex c(2,3);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
