// orbibiariel@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.h"
#include "../include/SquareMat.hpp"
#include <stdexcept>
#include <cmath>

using namespace MatrixNS;

// === Basic Functionality ===

TEST_CASE("Constructor and basic access") {
    SquareMat m(3);
    CHECK(m[0][0] == 0); // Check zero-initialization
    CHECK_THROWS_AS(SquareMat(-2), std::invalid_argument); // Invalid size
    CHECK_THROWS_AS((void)m[3][0], std::out_of_range);     // Out of bounds access
}

TEST_CASE("Copy constructor and assignment") {
    SquareMat m1(2);
    m1[0][0] = 5;
    SquareMat m2 = m1; // Copy constructor
    CHECK(m2[0][0] == 5);

    SquareMat m3(2);
    m3 = m1; // Assignment operator
    CHECK(m3[0][0] == 5);

    m1[0][0] = 10;
    CHECK(m2[0][0] == 5); // Ensure deep copy
    CHECK(m3[0][0] == 5);
}

// === Arithmetic Operations ===

TEST_CASE("Addition and subtraction") {
    SquareMat m1(2), m2(2);
    m1[0][0] = 1; m1[1][1] = 2;
    m2[0][0] = 3; m2[1][1] = 4;
    SquareMat sum = m1 + m2;
    SquareMat diff = m2 - m1;
    CHECK(sum[0][0] == 4);
    CHECK(diff[1][1] == 2);
    CHECK_THROWS_AS(m1 + SquareMat(3), std::invalid_argument);
}

TEST_CASE("Unary minus and scalar multiplication") {
    SquareMat m(2);
    m[0][0] = 2; m[1][1] = -3;
    SquareMat neg = -m;
    CHECK(neg[0][0] == -2);
    CHECK(neg[1][1] == 3);

    SquareMat mul1 = m * 2.0;
    SquareMat mul2 = 2.0 * m;
    CHECK(mul1[0][0] == 4);
    CHECK(mul2[1][1] == -6);
}

TEST_CASE("Element-wise multiplication and modulo") {
    SquareMat m1(2), m2(2);
    m1[0][0] = 6; m2[0][0] = 2;
    SquareMat res = m1 % m2;
    CHECK(res[0][0] == 12);
    CHECK((m1 % 4)[0][0] == fmod(6, 4));
}

TEST_CASE("Division and power") {
    SquareMat m(2);
    m[0][0] = 4; m[1][1] = 2;
    SquareMat div = m / 2.0;
    CHECK(div[0][0] == 2);
    CHECK_THROWS_AS(m / 0, std::invalid_argument);

    SquareMat identity = m ^ 0;
    CHECK(identity[0][0] == 1);
    CHECK(identity[1][1] == 1);
    CHECK_THROWS_AS(m ^ -1, std::invalid_argument);
}

// === Compound Assignment ===

TEST_CASE("Compound assignment with scalar") {
    SquareMat m(2);
    m[0][0] = 3;
    m *= 4;
    CHECK(m[0][0] == 12);
    m %= 5;
    CHECK(m[0][0] == fmod(12, 5));
}

TEST_CASE("Increment and compound assignment with matrices") {
    SquareMat m(2);
    ++m;
    CHECK(m[0][0] == 1);
    m += m;
    CHECK(m[0][0] == 2);
    m -= m;
    CHECK(m[0][0] == 0);
    m[0][0] = 5;
    m *= 2;
    CHECK(m[0][0] == 10);
    m %= 3;
    CHECK(m[0][0] == 10 % 3);
}

// === Operators and Logic ===

TEST_CASE("Postfix increment and decrement") {
    SquareMat m(2);
    m[0][0] = 1;
    SquareMat copy = m++;
    CHECK(copy[0][0] == 1);
    CHECK(m[0][0] == 2);

    copy = m--;
    CHECK(copy[0][0] == 2);
    CHECK(m[0][0] == 1);
}

TEST_CASE("Transpose and equality") {
    SquareMat m(2);
    m[0][1] = 5;
    SquareMat t = ~m;
    CHECK(t[1][0] == 5);

    SquareMat a(2), b(2);
    a[0][0] = 1; b[1][1] = 2;
    CHECK(!(a == b));
    CHECK(a != b);
}

TEST_CASE("Comparison operators") {
    SquareMat m1(2), m2(2), m3(3);
    m1[0][0] = 1; m1[1][1] = 2;
    m2[0][0] = 3; m2[1][1] = 4;
    m3[2][2]=3;
    CHECK(m2 > m1);
    CHECK(!(m1 >= m2));
    CHECK(m1 < m2);
    CHECK(m1 <= m2);
    CHECK(m2 >= m1);
    CHECK(m1 != m2);
    CHECK(m1 == m3);
    CHECK(m2 != m3);
    CHECK(m2 > m3);
    CHECK(m2 >= m3);
}

// === Determinant ===

TEST_CASE("Determinant of 2x2 and 3x3 matrices") {
    SquareMat m2(2);
    m2[0][0] = 1; m2[0][1] = 2;
    m2[1][0] = 3; m2[1][1] = 4;
    CHECK(!m2 == -2); // det = 1*4 - 2*3 = -2

    SquareMat m3(3);
    m3[0][0] = 6; m3[0][1] = 1; m3[0][2] = 1;
    m3[1][0] = 4; m3[1][1] = -2; m3[1][2] = 5;
    m3[2][0] = 2; m3[2][1] = 8; m3[2][2] = 7;
    CHECK(!m3 == -306); 
    // Determinant calculation:
    // 6 * ((-2)*7 - 5*8) - 1 * (4*7 - 5*2) + 1 * (4*8 - (-2)*2)
    // = 6 * (-54) - 1 * (18) + 1 * (36)
    //  = -324 - 18 + 36 = -306
}
