#include "FloatComplex.h"
#include <iostream>
using namespace std;
FloatComplex::FloatComplex() : IntComplex(), real(0.0f), imaginary(0.0f) {}
FloatComplex::FloatComplex(float realPart, float imaginaryPart) : IntComplex(0, 0), real(realPart), imaginary(imaginaryPart) {}

FloatComplex FloatComplex::operator+(const FloatComplex& other) const {
    float sumReal = real + other.real;
    float sumImaginary = imaginary + other.imaginary;
    return FloatComplex(sumReal, sumImaginary);
}
float FloatComplex::getReal() const {
    return real;
}
float FloatComplex::getImaginary() const {
    return imaginary;
}

FloatComplex FloatComplex::operator-(const FloatComplex& other) const {
    float diffReal = real - other.real;
    float diffImaginary = imaginary - other.imaginary;
    return FloatComplex(diffReal, diffImaginary);
}

FloatComplex FloatComplex::operator*(const FloatComplex& other) const {
    float mulReal = (real * other.real) - (imaginary * other.imaginary);
    float mulImaginary = (real * other.imaginary) + (imaginary * other.real);
    return FloatComplex(mulReal, mulImaginary);
}

FloatComplex FloatComplex::operator/(const FloatComplex& other) const {
    float denominator = (other.real * other.real) + (other.imaginary * other.imaginary);
    float divReal = ((real * other.real) + (imaginary * other.imaginary)) / denominator;
    float divImaginary = ((imaginary * other.real) - (real * other.imaginary)) / denominator;
    return FloatComplex(divReal, divImaginary);
}

void FloatComplex::print() const {
    cout << real << " + " << imaginary << "i" << std::endl;
}
