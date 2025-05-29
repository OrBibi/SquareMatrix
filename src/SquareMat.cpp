// orbibiariel@gmail.com
#include "../include/SquareMat.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>

using namespace MatrixNS;

// Allocate memory for the square matrix and initialize all elements to zero
void SquareMat::allocate() {
    data = new double*[size];
    for (int i = 0; i < size; ++i)
        data[i] = new double[size]{}; // zero-initialize
}

// Deep copy the content from another matrix
void SquareMat::copy(const SquareMat& other) {
    size = other.size;
    allocate();
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            data[i][j] = other.data[i][j];
}

// Free the allocated memory
void SquareMat::free() {
    for (int i = 0; i < size; ++i)
        delete[] data[i];
    delete[] data;
}

// Constructor with size, throws if size is not positive
SquareMat::SquareMat(int n) : size(n) {
    if (n <= 0) throw std::invalid_argument("Size must be positive");
    allocate();
}

// Copy constructor
SquareMat::SquareMat(const SquareMat& other) {
    copy(other);
}

// Assignment operator with self-assignment check
SquareMat& SquareMat::operator=(const SquareMat& other) {
    if (this != &other) {
        free();
        copy(other);
    }
    return *this;
}

// Destructor to release memory
SquareMat::~SquareMat() {
    free();
}

// Access element at row i (non-const version)
double* SquareMat::operator[](int i) {
    if (i < 0 || i >= size) throw std::out_of_range("Index out of range");
    return data[i];
}

// Access element at row i (const version)
const double* SquareMat::operator[](int i) const {
    if (i < 0 || i >= size) throw std::out_of_range("Index out of range");
    return data[i];
}

// Add two matrices element-wise
SquareMat SquareMat::operator+(const SquareMat& other) const {
    if (size != other.size) throw std::invalid_argument("Size mismatch");
    SquareMat result(size);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            result[i][j] = data[i][j] + other[i][j];
    return result;
}

// Subtract two matrices element-wise
SquareMat SquareMat::operator-(const SquareMat& other) const {
    if (size != other.size) throw std::invalid_argument("Size mismatch");
    SquareMat result(size);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            result[i][j] = data[i][j] - other[i][j];
    return result;
}

// Negate all matrix elements
SquareMat SquareMat::operator-() const {
    SquareMat result(size);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            result[i][j] = -data[i][j];
    return result;
}

// Matrix multiplication
SquareMat SquareMat::operator*(const SquareMat& other) const {
    if (size != other.size) throw std::invalid_argument("Size mismatch");
    SquareMat result(size);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            for (int k = 0; k < size; ++k)
                result[i][j] += data[i][k] * other[k][j];
    return result;
}

// Scalar multiplication
SquareMat SquareMat::operator*(double scalar) const {
    SquareMat result(size);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            result[i][j] = data[i][j] * scalar;
    return result;
}

// Scalar multiplication from left side
namespace MatrixNS {
SquareMat operator*(double scalar, const SquareMat& mat) {
    return mat * scalar;
}
}

// Element-wise multiplication
SquareMat SquareMat::operator%(const SquareMat& other) const {
    if (size != other.size) throw std::invalid_argument("Size mismatch");
    SquareMat result(size);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            result[i][j] = data[i][j] * other[i][j];
    return result;
}

// Element-wise modulo with an integer
SquareMat SquareMat::operator%(int mod) const {
    SquareMat result(size);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            result[i][j] = fmod(data[i][j], mod);
    return result;
}

// Scalar division
SquareMat SquareMat::operator/(double scalar) const {
    if (scalar == 0) throw std::invalid_argument("Division by zero");
    SquareMat result(size);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            result[i][j] = data[i][j] / scalar;
    return result;
}

// Raise matrix to a power (integer exponentiation)
SquareMat SquareMat::operator^(int power) const {
    if (power < 0) throw std::invalid_argument("Negative power not supported");
    SquareMat result(size);
    for (int i = 0; i < size; ++i)
        result[i][i] = 1; // identity matrix
    SquareMat base(*this);
    while (power) {
        if (power % 2) result = result * base;
        base = base * base;
        power /= 2;
    }
    return result;
}
// Binary Exponentiation link: https://cp-algorithms.com/algebra/binary-exp.html

// Compound assignment operators
SquareMat& SquareMat::operator+=(const SquareMat& other) { return *this = *this + other; }
SquareMat& SquareMat::operator-=(const SquareMat& other) { return *this = *this - other; }
SquareMat& SquareMat::operator*=(const SquareMat& other) { return *this = *this * other; }
SquareMat& SquareMat::operator*=(double scalar) { return *this = *this * scalar; }
SquareMat& SquareMat::operator%=(const SquareMat& other) { return *this = *this % other; }
SquareMat& SquareMat::operator%=(int mod) { return *this = *this % mod; }
SquareMat& SquareMat::operator/=(double scalar) { return *this = *this / scalar; }

// Pre-increment operator: increase each element by 1
SquareMat& SquareMat::operator++() {
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            ++data[i][j];
    return *this;
}

// Post-increment operator: increase each element by 1 (returns original state)
SquareMat SquareMat::operator++(int) {
    SquareMat temp(*this);
    ++(*this);
    return temp;
}

// Pre-decrement operator: decrease each element by 1
SquareMat& SquareMat::operator--() {
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            --data[i][j];
    return *this;
}

// Post-decrement operator: decrease each element by 1 (returns original state)
SquareMat SquareMat::operator--(int) {
    SquareMat temp(*this);
    --(*this);
    return temp;
}

// Transpose the matrix
SquareMat SquareMat::operator~() const {
    SquareMat result(size);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            result[j][i] = data[i][j];
    return result;
}

// Equality operator: compares the sum of elements
bool SquareMat::operator==(const SquareMat& other) const {
    double sum1 = 0, sum2 = 0;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j) {
            sum1 += data[i][j];
        }
    for (int i = 0; i < other.size; ++i)
        for (int j = 0; j < other.size; ++j) {
            sum2 += other.data[i][j];
        }
    return sum1 == sum2;
}

// Inequality operator
bool SquareMat::operator!=(const SquareMat& other) const {
    return !(*this == other);
}

// Less-than operator: compares sum of elements
bool SquareMat::operator<(const SquareMat& other) const {
    double sum1 = 0, sum2 = 0;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j) {
            sum1 += data[i][j];
        }
    for (int i = 0; i < other.size; ++i)
        for (int j = 0; j < other.size; ++j) {
            sum2 += other.data[i][j];
        }
    return sum1 < sum2;
}

// Greater-than operator
bool SquareMat::operator>(const SquareMat& other) const {
    return other < *this;
}

// Less-than-or-equal operator
bool SquareMat::operator<=(const SquareMat& other) const {
    return !(other < *this);
}

// Greater-than-or-equal operator
bool SquareMat::operator>=(const SquareMat& other) const {
    return !(*this < other);
}

// Determinant using recursive expansion
double SquareMat::operator!() const {
    // Base case: 1x1 matrix
    if (size == 1) return data[0][0];

    // Base case: 2x2 matrix
    if (size == 2)
        return data[0][0] * data[1][1] - data[0][1] * data[1][0];

    double det = 0;

    // Recursive case:
    for (int k = 0; k < size; ++k) {
        SquareMat sub(size - 1);  // Create minor matrix

        // Fill submatrix by skipping row 0 and column k
        for (int i = 1; i < size; ++i) { // start from row 1 (skip row 0)
            int colIndex = 0;
            for (int j = 0; j < size; ++j) {
                if (j == k) continue; // skip column k
                sub[i - 1][colIndex++] = data[i][j];
            }
        }

        // Add cofactor: sign alternates by column (even: +, odd: -)
        det += (k % 2 == 0 ? 1 : -1) * data[0][k] * !sub;
    }

    return det;
}


// Output matrix to an output stream.
namespace MatrixNS {
std::ostream& operator<<(std::ostream& os, const SquareMat& mat) {
    for (int i = 0; i < mat.size; ++i) {
        for (int j = 0; j < mat.size; ++j)
            os << mat[i][j] << " ";
        os << "\n";
    }
    return os;
}
}
