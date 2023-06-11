#ifndef FLOATCOMPLEX_H
#define FLOATCOMPLEX_H

#include "IntComplex.h"

class FloatComplex : public IntComplex {
private:
    float real;
    float imaginary;

public:
	FloatComplex();
    FloatComplex(float realPart, float imaginaryPart);
	float getReal() const;
	float getImaginary() const;
    FloatComplex operator+(const FloatComplex& other) const;
    FloatComplex operator-(const FloatComplex& other) const;
    FloatComplex operator*(const FloatComplex& other) const;
    FloatComplex operator/(const FloatComplex& other) const;

    void print() const;
};

#endif
