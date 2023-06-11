#include "IntComplex.h"
#include <iostream>
using namespace std;
IntComplex::IntComplex() : real(0), imaginary(0) {}
IntComplex::IntComplex(int realPart, int imaginaryPart) : real(realPart), imaginary(imaginaryPart) {}

int IntComplex::getReal() const {
    return real;
}
int IntComplex::getImaginary() const {
    return imaginary;
}
IntComplex IntComplex::operator+(const IntComplex& other) const {
    int sumReal = real + other.real;
    int sumImaginary = imaginary + other.imaginary;
    return IntComplex(sumReal, sumImaginary);
}

IntComplex IntComplex::operator-(const IntComplex& other) const {
    int diffReal = real - other.real;
    int diffImaginary = imaginary - other.imaginary;
    return IntComplex(diffReal, diffImaginary);
}

IntComplex IntComplex::operator*(const IntComplex& other) const {
    int mulReal = (real * other.real) - (imaginary * other.imaginary);
    int mulImaginary = (real * other.imaginary) + (imaginary * other.real);
    return IntComplex(mulReal, mulImaginary);
}

IntComplex IntComplex::operator/(const IntComplex& other) const {
    int denominator = (other.real * other.real) + (other.imaginary * other.imaginary);
    int divReal = ((real * other.real) + (imaginary * other.imaginary)) / denominator;
    int divImaginary = ((imaginary * other.real) - (real * other.imaginary)) / denominator;
    return IntComplex(divReal, divImaginary);
}

void IntComplex::print() const {
    cout << real << " + " << imaginary << "i" << endl;
}
