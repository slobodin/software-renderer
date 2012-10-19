/*
 * test_vec_matr_4x4.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include <gtest/gtest.h>
#include "m44.h"
#include "vec3.h"

using namespace math;

TEST(Matrix4x4, DefaultConstructor)
{
    M44 m;

    EXPECT_EQ(1, m.x[0][0]);
    EXPECT_EQ(0, m.x[0][1]);
    EXPECT_EQ(0, m.x[0][2]);
    EXPECT_EQ(0, m.x[0][3]);

    EXPECT_EQ(0, m.x[1][0]);
    EXPECT_EQ(1, m.x[1][1]);
    EXPECT_EQ(0, m.x[1][2]);
    EXPECT_EQ(0, m.x[1][3]);

    EXPECT_EQ(0, m.x[2][0]);
    EXPECT_EQ(0, m.x[2][1]);
    EXPECT_EQ(1, m.x[2][2]);
    EXPECT_EQ(0, m.x[2][3]);

    EXPECT_EQ(0, m.x[3][0]);
    EXPECT_EQ(0, m.x[3][1]);
    EXPECT_EQ(0, m.x[3][2]);
    EXPECT_EQ(1, m.x[3][3]);
}

TEST(Matrix4x4, ArrayConstructor)
{
    const float in[4][4] = { { 1, 2, 3, 4 },
                              { 5, 6, 7, 8 },
                              { 9, 10, 11, 12 },
                              { 13, 14, 15, 16 } };
    M44 m(in);

    EXPECT_EQ(1, m.x[0][0]);
    EXPECT_EQ(2, m.x[0][1]);
    EXPECT_EQ(3, m.x[0][2]);
    EXPECT_EQ(4, m.x[0][3]);

    EXPECT_EQ(5, m.x[1][0]);
    EXPECT_EQ(6, m.x[1][1]);
    EXPECT_EQ(7, m.x[1][2]);
    EXPECT_EQ(8, m.x[1][3]);

    EXPECT_EQ(9, m.x[2][0]);
    EXPECT_EQ(10, m.x[2][1]);
    EXPECT_EQ(11, m.x[2][2]);
    EXPECT_EQ(12, m.x[2][3]);

    EXPECT_EQ(13, m.x[3][0]);
    EXPECT_EQ(14, m.x[3][1]);
    EXPECT_EQ(15, m.x[3][2]);
    EXPECT_EQ(16, m.x[3][3]);
}

TEST(Matrix4x4, StandartConstructor)
{
    M44 m(1, 2, 3, 4,
          5, 6, 7, 8,
          9, 10, 11, 12,
          13, 14, 15, 16);

    EXPECT_EQ(1, m.x[0][0]);
    EXPECT_EQ(2, m.x[0][1]);
    EXPECT_EQ(3, m.x[0][2]);
    EXPECT_EQ(4, m.x[0][3]);

    EXPECT_EQ(5, m.x[1][0]);
    EXPECT_EQ(6, m.x[1][1]);
    EXPECT_EQ(7, m.x[1][2]);
    EXPECT_EQ(8, m.x[1][3]);

    EXPECT_EQ(9, m.x[2][0]);
    EXPECT_EQ(10, m.x[2][1]);
    EXPECT_EQ(11, m.x[2][2]);
    EXPECT_EQ(12, m.x[2][3]);

    EXPECT_EQ(13, m.x[3][0]);
    EXPECT_EQ(14, m.x[3][1]);
    EXPECT_EQ(15, m.x[3][2]);
    EXPECT_EQ(16, m.x[3][3]);
}

static const M44 A(1, 3, 4, 18,
                   5, 8, 0, 67,
                   -2, 4, -10, 6,
                   9, 15, 47, 28);
static const M44 B(5, 8, 9, 1,
                   -3, 5, 1, 2,
                   6, 11, 2, 6,
                   13, 18, 76, 8);

TEST(Matrix4x4, AssignOperations)
{
    M44 a(A);
    M44 b(B);

    // addition
    a += b;
    EXPECT_TRUE(a == M44(6, 11, 13, 19,
                         2, 13, 1, 69,
                         4, 15, -8, 12,
                         22, 33, 123, 36));

    // subtraction
    a -= b;
    EXPECT_TRUE(a == A);
    EXPECT_TRUE(b == B);

    // multiplication
    a *= b;
    EXPECT_TRUE(a == M44(254, 391, 1388, 175,
                         872, 1286, 5145, 557,
                         -4, 2, 422, -6,
                         646, 1168, 2318, 545));

    // scalar operations
    b *= 3;
    EXPECT_TRUE(b == M44(15, 24, 27, 3,
                         -9, 15, 3, 6,
                         18, 33, 6, 18,
                         39, 54, 228, 24));

    b /= 3;
    EXPECT_TRUE(b == B);
}


TEST(Matrix4x4, MatrixTranspose)
{
    M44 a(A);

    a.transpose();
    EXPECT_TRUE(a == M44(1, 5, -2, 9,
                         3, 8, 4, 15,
                         4, 0, -10, 47,
                         18, 67, 6, 28));
}

TEST(Matrix4x4, MatrixOperations)
{
    M44 a(A), b(B);
    M44 c;

    c = a + b;
    EXPECT_TRUE(c == M44(6, 11, 13, 19,
                         2, 13, 1, 69,
                         4, 15, -8, 12,
                         22, 33, 123, 36));

    c = a - b;
    EXPECT_TRUE(c == M44(-4, -5, -5, 17,
                         8, 3, -1, 65,
                         -8, -7, -12, 0,
                         -4, -3, -29, 20));

    c = a * b;
    EXPECT_TRUE(c == M44(254, 391, 1388, 175,
                         872, 1286, 5145, 557,
                         -4, 2, 422, -6,
                         646, 1168, 2318, 545));

    c = a * 2;
    EXPECT_TRUE(c == M44(2, 6, 8, 36,
                         10, 16, 0, 134,
                         -4, 8, -20, 12,
                         18, 30, 94, 56));

    c = 2 * a;
    EXPECT_TRUE(c == M44(2, 6, 8, 36,
                         10, 16, 0, 134,
                         -4, 8, -20, 12,
                         18, 30, 94, 56));

    vec3 v(52, 18, -2), vres;
    vres = v * A;

    EXPECT_TRUE(vres == vec3(0.071825765, 0.142261353, 0.127432808));
}
