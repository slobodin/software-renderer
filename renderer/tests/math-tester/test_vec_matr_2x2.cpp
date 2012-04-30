/*
 * test_vec_matr_2x2.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include <gtest/gtest.h>
#include <cstdint>
#include "m22.h"

using namespace math;

// Vectors
TEST(Vector2, Constructors)
{
    vec2 a, b(1, 5);

    EXPECT_TRUE(a == vec2(0, 0));
    EXPECT_TRUE(b == vec2(1, 5));
}

TEST(Vector2, AssignOperations)
{
    vec2 a(6, 4), b(1, 5);

    a += b;
    EXPECT_TRUE(a == vec2(7, 9));

    a -= b;
    EXPECT_TRUE(a == vec2(6, 4));

    a *= 2;
    EXPECT_TRUE(a == vec2(12, 8));

    a /= 2;
    EXPECT_TRUE(a == vec2(6, 4));
}

TEST(Vector2, Flip)
{
    vec2 a(6, 4), b;

    b = -a;

    EXPECT_TRUE(a == vec2(6, 4));
    EXPECT_TRUE(b == vec2(-6, -4));
}

TEST(Vector2, VectorOperations)
{
    vec2 a(6, 4), b(6, 4);

    // length
    EXPECT_NEAR(7.2111, a.length(), EPSILON_E3);

    // normalization
    a.normalize();
    EXPECT_TRUE(a == vec2(0.83205, 0.5547));

    // scalar product
    EXPECT_NEAR(7.2111, a.dotProduct(b), EPSILON_E3);

    a.set(6, 4);
    b.set(6, 4);
    EXPECT_TRUE(a == vec2(6, 4));
    EXPECT_TRUE(b == vec2(6, 4));

    vec2 c;

    c = a + b;
    EXPECT_TRUE(c == vec2(12, 8));

    c = a - b;
    EXPECT_TRUE(c == vec2(0, 0));

    c = 3 * a;
    EXPECT_TRUE(c == vec2(18, 12));

    c = b * 3;
    EXPECT_TRUE(c == vec2(18, 12));

    c = b / 2;
    EXPECT_TRUE(c == vec2(3, 2));
}

// Matrices
TEST(Matrix2x2, DefaultConstructor)
{
    M22 m;

    EXPECT_EQ(1, m.x[0]);
    EXPECT_EQ(0, m.x[1]);
    EXPECT_EQ(0, m.x[2]);
    EXPECT_EQ(1, m.x[3]);
}

TEST(Matrix2x2, ArrayConstructor)
{
    const double in[4] = { 5, 7, 4, 3 };
    M22 m(in);

    EXPECT_EQ(5, m.x[0]);
    EXPECT_EQ(7, m.x[1]);
    EXPECT_EQ(4, m.x[2]);
    EXPECT_EQ(3, m.x[3]);
}

TEST(Matrix2x2, StandartConstructor)
{
    M22 m(1, 5, 7, 0);

    EXPECT_EQ(1, m.x[0]);
    EXPECT_EQ(5, m.x[1]);
    EXPECT_EQ(7, m.x[2]);
    EXPECT_EQ(0, m.x[3]);
}

TEST(Matrix2x2, AssignOperations)
{
    M22 a(1, 3, 4, 5), b(5, 8, 9, -3);

    // addition
    a += b;
    EXPECT_TRUE(a == M22(6, 11, 13, 2));

    // subtraction
    a -= b;
    EXPECT_TRUE(a == M22(1, 3, 4, 5));

    // multiplication
    a *= b;
    EXPECT_TRUE(a == M22(32, -1, 65, 17));

    // scalar operations
    b *= 3;
    EXPECT_TRUE(b == M22(15, 24, 27, -9));

    b /= 3;
    EXPECT_TRUE(b == M22(5, 8, 9, -3));

//    ASSERT_DEATH({ M22 a; a /= 0; } , "!DCMP(s, 0.0)");
}

TEST(Matrix2x2, MatrixTranspose)
{
    M22 a(34, 18, 9, 0);

    a.transpose();
    EXPECT_TRUE(a == M22(34, 9, 18, 0));
}

TEST(Matrix2x2, MatrixInvert)
{
    M22 a(18, 6, 123, -79);

    a.invert();
    EXPECT_TRUE(a == M22(0.037, 0.003, 0.057, -0.008));
}

TEST(Matrix2x2, MatrixDeterminant)
{
    M22 a(5, 1, 6, 3);

    EXPECT_EQ(9, a.determinant());
}

TEST(Matrix2x2, MatrixOperations)
{
    M22 a(1, 3, 4, 5), b(5, 8, 9, -3);
    M22 c;

    c = a + b;
    EXPECT_TRUE(c == M22(6, 11, 13, 2));

    c = a - b;
    EXPECT_TRUE(c == M22(-4, -5, -5, 8));

    c = a * b;
    EXPECT_TRUE(c == M22(32, -1, 65, 17));

    c = a * 2;
    EXPECT_TRUE(c == M22(2, 6, 8, 10));

    c = 2 * a;
    EXPECT_TRUE(c == M22(2, 6, 8, 10));

    vec2 v(3, 60), vres;
    vres = v * b;
    EXPECT_TRUE(vres == vec2(555, -156));
}
