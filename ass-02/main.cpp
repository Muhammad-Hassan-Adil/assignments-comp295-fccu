#include <iostream>
#include <cstdlib>
#include "IntComplex.h"
#include "FloatComplex.h"
#include <iomanip>

using namespace std;

int main(int argc, char* argv[]) {
    // command line args and initializing numbers
    int intReal1 = atoi(argv[1]);
    int intImaginary1 = atoi(argv[2]);
    int intReal2 = atoi(argv[3]);
    int intImaginary2 = atoi(argv[4]);
    float floatReal1 = atof(argv[5]);
    float floatImaginary1 = atof(argv[6]);
    float floatReal2 = atof(argv[7]);
    float floatImaginary2 = atof(argv[8]);

    // Class calls
    IntComplex intComplex1(intReal1, intImaginary1);
    IntComplex intComplex2(intReal2, intImaginary2);
    FloatComplex floatComplex1(floatReal1, floatImaginary1);
    FloatComplex floatComplex2(floatReal2, floatImaginary2);

    // Print the integer complex numbers
    cout << "First Integer Complex Number:" << endl;
    intComplex1.print();
    cout << "Second Integer Complex Number:" << endl;
    intComplex2.print();
    cout << "First Float Complex Number:" << endl;
    floatComplex1.print();
    cout << "Second Float Complex Number:" << endl;
    floatComplex2.print();

    // Perform operations and print the results for Integer Complex
    IntComplex intSum = intComplex1 + intComplex2;
    IntComplex intSubtraction = intComplex1 - intComplex2;
    IntComplex intMultiplication = intComplex1 * intComplex2;
    IntComplex intDivision = intComplex1 / intComplex2;

    cout << "Integer Complex Results:" << endl;
    //Addition
    cout << "Sum of complex numbers: ";
    intSum.print();
    // Substraction
    cout << "Subtraction of complex numbers: ";
    intSubtraction.print();
    // multiplication
    cout << "Multiplication of complex numbers: ";
    intMultiplication.print();
    // division
    cout << "Division of complex numbers: ";
    if (intComplex2.getReal() == 0 && intComplex2.getImaginary() == 0) {
        cout << "Error: Division by zero is not allowed." << endl;
    } else {
        IntComplex intDivision = intComplex1 / intComplex2;
        intDivision.print();
    }

    // Perform operations and print the results for Float Complex
    FloatComplex floatSum = floatComplex1 + floatComplex2;
    FloatComplex floatSubtraction = floatComplex1 - floatComplex2;
    FloatComplex floatMultiplication = floatComplex1 * floatComplex2;
    FloatComplex floatDivision = floatComplex1 / floatComplex2;

    cout << "Float Complex Results:" << endl;
    cout << fixed << setprecision(2); // Set precision to 2 decimal places

    cout << "Sum of complex numbers: ";
    floatSum.print();
    cout << "Subtraction of complex numbers: ";
    floatSubtraction.print();
    cout << "Multiplication of complex numbers: ";
    floatMultiplication.print();
    cout << "Division of complex numbers: ";
    if (floatComplex2.getReal() == 0.0 && floatComplex2.getImaginary() == 0.0) {
        cout << "Error: Division by zero not allowed!!!" << endl;
    } else {
        FloatComplex floatDivision = floatComplex1 / floatComplex2;
        floatDivision.print();
    }

    return 0;
}
