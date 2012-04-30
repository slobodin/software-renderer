/*
 * test_vec_matr_3x3.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include <gtest/gtest.h>
#include "vec3.h"
#include "m33.h"

using namespace math;

// Vectors
TEST(Vector3, Constructors)
{
    vec3 a, b(1, 5, 8);

    EXPECT_TRUE(a == vec3(0, 0, 0));
    EXPECT_TRUE(b == vec3(1, 5, 8));
}

TEST(Vector3, AssignOperations)
{
    vec3 a(6, 4, 2), b(1, 5, 7);

    a += b;
    EXPECT_TRUE(a == vec3(7, 9, 9));

    a -= b;
    EXPECT_TRUE(a == vec3(6, 4, 2));

    a *= 2;
    EXPECT_TRUE(a == vec3(12, 8, 4));

    a /= 2;
    EXPECT_TRUE(a == vec3(6, 4, 2));
}

TEST(Vector3, FlipAndEquality)
{
    vec3 a(6, 4, -7), b;

    b = -a;

    EXPECT_TRUE(a == vec3(6, 4, -7));
    EXPECT_TRUE(b == vec3(-6, -4, 7));
    EXPECT_TRUE(a != b);
}

TEST(Vector3, IsZero)
{
    vec3 a;

    EXPECT_TRUE(a.isZero());

    a.set(0.0000001, 0.0000001, 0.0000001);
    EXPECT_TRUE(a.isZero());

    a.set(100, 456, 987);
    a.zero();
    EXPECT_TRUE(a.isZero());

    a.set(1, 2, 3);
    EXPECT_FALSE(a.isZero());
}


TEST(Vector3, VectorOperations)
{
    vec3 a(6, 4, 4), b(6, 4, 1);

    // length
    EXPECT_NEAR(8.246, a.length(), EPSILON_E3);

    // normalization
    a.normalize();
    EXPECT_TRUE(a == vec3(0.728, 0.485, 0.485));
    EXPECT_NEAR(1.0, a.length(), EPSILON_E3);

    a.set(0.728, 0.485, 0.485);

    // scalar product
    EXPECT_NEAR(6.793, a.dotProduct(b), EPSILON_E3);

    a.set(6, 4, 3);
    b.set(6, 4, 5);
    EXPECT_TRUE(a == vec3(6, 4, 3));
    EXPECT_TRUE(b == vec3(6, 4, 5));

    vec3 c;

    // addition, subtraction, multipliaction and division
    c = a + b;
    EXPECT_TRUE(c == vec3(12, 8, 8));

    c = a - b;
    EXPECT_TRUE(c == vec3(0, 0, -2));

    c = 3 * a;
    EXPECT_TRUE(c == vec3(18, 12, 9));

    c = b * 3;
    EXPECT_TRUE(c == vec3(18, 12, 15));

    c = b / 2;
    EXPECT_TRUE(c == vec3(3, 2, 2.5));

    // sanity check
    EXPECT_TRUE(a == vec3(6, 4, 3));
    EXPECT_TRUE(b == vec3(6, 4, 5));

    // cross product
    c = a.crossProduct(b);
    EXPECT_TRUE(c == vec3(8, -12, 0));
}

// Matrices tests

static const M33 A(1, 3, 4,
                   5, 8, 0,
                   -2, 4, -10);
static const M33 B(5, 8, 9,
                   -3, 5, 1,
                   6, 11, 2);

TEST(Matrix3x3, DefaultConstructor)
{
    M33 m;

    EXPECT_EQ(1, m.x[0][0]);
    EXPECT_EQ(0, m.x[0][1]);
    EXPECT_EQ(0, m.x[0][2]);
    EXPECT_EQ(0, m.x[1][0]);
    EXPECT_EQ(1, m.x[1][1]);
    EXPECT_EQ(0, m.x[1][2]);
    EXPECT_EQ(0, m.x[2][0]);
    EXPECT_EQ(0, m.x[2][1]);
    EXPECT_EQ(1, m.x[2][2]);
}

TEST(Matrix3x3, ArrayConstructor)
{
    const double in[3][3] = { { 1, 2, 3 },
                              { 4, 5, 6 },
                              { 7, 8, 9 } };
    M33 m(in);

    EXPECT_EQ(1, m.x[0][0]);
    EXPECT_EQ(2, m.x[0][1]);
    EXPECT_EQ(3, m.x[0][2]);
    EXPECT_EQ(4, m.x[1][0]);
    EXPECT_EQ(5, m.x[1][1]);
    EXPECT_EQ(6, m.x[1][2]);
    EXPECT_EQ(7, m.x[2][0]);
    EXPECT_EQ(8, m.x[2][1]);
    EXPECT_EQ(9, m.x[2][2]);
}

TEST(Matrix3x3, StandartConstructor)
{
    M33 m(1, 2, 3,
          4, 5, 6,
          7, 8, 9);

    EXPECT_EQ(1, m.x[0][0]);
    EXPECT_EQ(2, m.x[0][1]);
    EXPECT_EQ(3, m.x[0][2]);
    EXPECT_EQ(4, m.x[1][0]);
    EXPECT_EQ(5, m.x[1][1]);
    EXPECT_EQ(6, m.x[1][2]);
    EXPECT_EQ(7, m.x[2][0]);
    EXPECT_EQ(8, m.x[2][1]);
    EXPECT_EQ(9, m.x[2][2]);
}

TEST(Matrix3x3, AssignOperations)
{
    M33 a(A);
    M33 b(B);

    // addition
    a += b;
    EXPECT_TRUE(a == M33(6, 11, 13,
                         2, 13, 1,
                         4, 15, -8));

    // subtraction
    a -= b;
    EXPECT_TRUE(a == A);

    // multiplication
    a *= b;
    EXPECT_TRUE(a == M33(20, 67, 20,
                         1, 80, 53,
                         -82, -106, -34));

    // scalar operations
    b *= 3;
    EXPECT_TRUE(b == M33(15, 24, 27,
                         -9, 15, 3,
                         18, 33, 6));

    b /= 3;
    EXPECT_TRUE(b == B);
}


TEST(Matrix3x3, MatrixTranspose)
{
    M33 a(A);

    a.transpose();
    EXPECT_TRUE(a == M33(1, 5, -2,
                         3, 8, 4,
                         4, 0, -10));
}

TEST(Matrix3x3, MatrixInvert)
{
    M33 a(A);

    a.invert();
    EXPECT_TRUE(a == M33(-0.37383177570093, 0.21495327102804, -0.14953271028037,
                         0.23364485981308, -0.0093457943925234, 0.093457943925234,
                         0.16822429906542, -0.046728971962617, -0.032710280373832));
}

TEST(Matrix3x3, MatrixDeterminant)
{
    M33 a(A);

    EXPECT_EQ(214, a.determinant());
}

TEST(Matrix3x3, MatrixOperations)
{
    M33 a(A), b(B);
    M33 c;

    c = a + b;
    EXPECT_TRUE(c == M33(6, 11, 13,
                         2, 13, 1,
                         4, 15, -8));

    c = a - b;
    EXPECT_TRUE(c == M33(-4, -5, -5,
                         8, 3, -1,
                         -8, -7, -12));

    c = a * b;
    EXPECT_TRUE(c == M33(20, 67, 20,
                         1, 80, 53,
                         -82, -106, -34));

    c = a * 2;
    EXPECT_TRUE(c == M33(2, 6, 8,
                         10, 16, 0,
                         -4, 8, -20));

    c = 2 * a;
    EXPECT_TRUE(c == M33(2, 6, 8,
                         10, 16, 0,
                         -4, 8, -20));

    vec3 v(3, 60, 5), vres;
    vres = v * A;
    EXPECT_TRUE(vres == vec3(293, 509, -38));
}
