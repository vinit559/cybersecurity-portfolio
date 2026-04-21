#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <cmath>

class Complex {
public:
    double real{0}, imag{0};

    // Constructor
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // Addition
    Complex operator+(const Complex& obj) const {
        return Complex(real + obj.real, imag + obj.imag);
    }

    // Subtraction
    Complex operator-(const Complex& obj) const {
        return Complex(real - obj.real, imag - obj.imag);
    }

    // Multiplication (complex)
    Complex operator*(const Complex& obj) const {
        return Complex(real * obj.real - imag * obj.imag,
                       real * obj.imag + imag * obj.real);
    }

    // Conjugate
    Complex conjugate() const {
        return Complex(real, -imag);
    }

    // Magnitude (squared and actual)
    double magnitude2() const { return real * real + imag * imag; }
    double magnitude() const { return std::sqrt(magnitude2()); }

    // Division
    Complex operator/(const Complex& obj) const {
        double denom = obj.magnitude2();
        if (denom == 0.0) {
            throw std::runtime_error("division by zero in Complex::operator/");
        }
        Complex num = (*this) * obj.conjugate();
        return Complex(num.real / denom, num.imag / denom);
    }

    // Equality (approximate with epsilon)
    static double defaultEpsilon() { return 1e-9; }
    bool operator==(const Complex& other) const {
        return approxEquals(other, defaultEpsilon());
    }

    bool operator!=(const Complex& other) const { return !(*this == other); }

    // Approximate equality with epsilon
    bool approxEquals(const Complex& other, double eps = defaultEpsilon()) const {
        return std::fabs(real - other.real) <= eps && std::fabs(imag - other.imag) <= eps;
    }

    // Unary negation
    Complex operator-() const { return Complex(-real, -imag); }

    // Bitwise-looking operator for conjugate
    Complex operator~() const { return conjugate(); }

    // Approximate equality with epsilon
    bool approxEquals(const Complex& other, double eps = 1e-9) const {
        return std::fabs(real - other.real) <= eps && std::fabs(imag - other.imag) <= eps;
    }

    // Scalar operations
    Complex operator*(double s) const { return Complex(real * s, imag * s); }
    Complex operator/(double s) const {
        if (s == 0.0) throw std::runtime_error("division by zero in Complex::operator/(double)");
        return Complex(real / s, imag / s);
    }

    // Compound assignment
    Complex& operator+=(const Complex& o) { real += o.real; imag += o.imag; return *this; }
    Complex& operator-=(const Complex& o) { real -= o.real; imag -= o.imag; return *this; }
    Complex& operator*=(const Complex& o) { *this = *this * o; return *this; }
    Complex& operator/=(const Complex& o) { *this = *this / o; return *this; }

    // scalar compound
    Complex& operator*=(double s) { real *= s; imag *= s; return *this; }
    Complex& operator/=(double s) { if (s==0.0) throw std::runtime_error("division by zero"); real/=s; imag/=s; return *this; }

    // Print helper
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real << " + " << c.imag << "i";
        return os;
    }
};

#endif // COMPLEX_H
