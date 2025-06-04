// orbibiariel@gmail.com
#include "../include/SquareMat.hpp"
#include <iostream>

using namespace MatrixNS;

int main() {
    std::cout << "=== Square Matrix Demonstration ===" << std::endl;

    // Create a 3x3 matrix and initialize values
    SquareMat A(3);
    A[0][0] = 6; A[0][1] = 1; A[0][2] = 1;
    A[1][0] = 4; A[1][1] = -2; A[1][2] = 5;
    A[2][0] = 2; A[2][1] = 8; A[2][2] = 7;

    std::cout << "Matrix A:\n" << A << std::endl;

    // Compute determinant
    double detA = !A;
    std::cout << "Determinant of A: " << detA << std::endl;

    // Scalar multiplication
    SquareMat B = A * 2;
    std::cout << "Matrix B = A * 2:\n" << B << std::endl;

    // Matrix addition
    SquareMat C = A + B;
    std::cout << "Matrix C = A + B:\n" << C << std::endl;

    // Transpose
    SquareMat At = ~A;
    std::cout << "Transpose of A:\n" << At << std::endl;

    // Power (A^2)
    SquareMat Apow = A ^ 2;
    std::cout << "A squared (A^2):\n" << Apow << std::endl;

    return 0;
}

