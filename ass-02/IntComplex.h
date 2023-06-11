#ifndef INTCOMPLEX_H
#define INTCOMPLEX_H

class IntComplex {
private:
    int real;
    int imaginary;

public:
	IntComplex();
    IntComplex(int realPart, int imaginaryPart);
	int getReal() const;
	int getImaginary() const;
    IntComplex operator+(const IntComplex& other) const;
    IntComplex operator-(const IntComplex& other) const;
    IntComplex operator*(const IntComplex& other) const;
    IntComplex operator/(const IntComplex& other) const;
    void print() const;
};

#endif
