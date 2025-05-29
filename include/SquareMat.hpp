// orbibiariel@gmail.com
#pragma once
#include <iostream>
#include <stdexcept>
#include <cmath>

namespace MatrixNS {

// Class representing a square matrix of doubles
class SquareMat {
private:
    int size;              // Size of the matrix (NxN)
    double** data;         // Pointer to 2D dynamic array storing matrix data

    void allocate();                   // Allocate memory for the matrix
    void copy(const SquareMat& other); // Copy data from another matrix
    void free();                       // Free allocated memory

public:
    SquareMat(int n);                         // Constructor with size
    SquareMat(const SquareMat& other);        // Copy constructor
    SquareMat& operator=(const SquareMat& other); // Assignment operator
    ~SquareMat();                             // Destructor

    double* operator[](int i);                // Access row i (non-const)
    const double* operator[](int i) const;    // Access row i (const)

    SquareMat operator+(const SquareMat& other) const; // Matrix addition
    SquareMat operator-(const SquareMat& other) const; // Matrix subtraction
    SquareMat operator-() const;                        // Negate matrix
    SquareMat operator*(const SquareMat& other) const;  // Matrix multiplication
    SquareMat operator*(double scalar) const;           // Scalar multiplication
    SquareMat operator%(const SquareMat& other) const;  // Element-wise multiplication
    SquareMat operator%(int mod) const;                 // Element-wise modulo
    SquareMat operator/(double scalar) const;           // Scalar division
    SquareMat operator^(int power) const;               // Matrix exponentiation

    // Compound assignment operators
    SquareMat& operator+=(const SquareMat& other); 
    SquareMat& operator-=(const SquareMat& other);
    SquareMat& operator*=(const SquareMat& other);
    SquareMat& operator*=(double scalar);
    SquareMat& operator%=(const SquareMat& other);
    SquareMat& operator%=(int mod);
    SquareMat& operator/=(double scalar);

    SquareMat& operator++();    // Pre-increment: increment all elements
    SquareMat operator++(int);  // Post-increment: return original, then increment
    SquareMat& operator--();    // Pre-decrement: decrement all elements
    SquareMat operator--(int);  // Post-decrement: return original, then decrement

    SquareMat operator~() const; // Transpose the matrix

    // Comparison operators based on sum of elements
    bool operator==(const SquareMat& other) const;
    bool operator!=(const SquareMat& other) const;
    bool operator<(const SquareMat& other) const;
    bool operator>(const SquareMat& other) const;
    bool operator<=(const SquareMat& other) const;
    bool operator>=(const SquareMat& other) const;

    double operator!() const; // Compute determinant of the matrix

    // Friend functions for scalar multiplication and stream output
    friend SquareMat operator*(double scalar, const SquareMat& mat);
    friend std::ostream& operator<<(std::ostream& os, const SquareMat& mat);
};

}
