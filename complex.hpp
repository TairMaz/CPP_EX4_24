// Tair Mazriv
// id: 209188382
// tairmazriv@gmail.com

#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>

class Complex {
public:
    double real, imag;

    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    bool operator==(const Complex& other) const {
        return (real == other.real && imag == other.imag);
    }

    double magnitude() const {
        return std::sqrt(real * real + imag * imag);
    }

    // Overloading the < operator
    bool operator<(const Complex& other) const {
        return this->magnitude() < other.magnitude();
    }

    // Output stream operator overload for printing Complex numbers
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        return os << c.real << " + " << c.imag << "i";
    }
};

#endif // COMPLEX_HPP

