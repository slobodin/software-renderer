/*
 * test_math_utils.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include <gtest/gtest.h>
#include "math_utils.h"

using namespace math;

TEST(AngleBetween, TwoDim)
{
    vec2 a(1, 5), b(1, 5);

    double angle = AngleBetween(a, b);
    EXPECT_NEAR(0, angle, 0.0001);

    a.set(5, 1);
    angle = AngleBetween(a, b);
    EXPECT_NEAR(67.38014, angle, 0.0001);
}

TEST(AngleBetween, ThreeDim)
{
    vec3 a, b(5, 8, 7);
    a = b;

    double angle = AngleBetween(a, b);
    EXPECT_NEAR(0, angle, 0.0001);

    a.set(5, 6, 7);
    angle = AngleBetween(a, b);
    EXPECT_NEAR(8.027017644, angle, 0.0001);
}

TEST(LinesIntersection, TwoDim)
{
    vec2 p0(1, 1), p1(8, 5);    // first line
    vec2 p2(3, 6), p3(8, 3);    // second line

    // intersection
    vec2 resultPt;
    LinesIntersectionType res = CheckLinesIntersection(p0, p1, p2, p3, resultPt);
    EXPECT_NEAR(6.29, resultPt.x, 0.01);
    EXPECT_NEAR(4.02, resultPt.y, 0.01);
    EXPECT_EQ(res, LINES_INTERSECT_IN_SEGMENT);

    // from one point
    p2.set(1, 2); p3.set(8, 5);
    res = CheckLinesIntersection(p0, p1, p2, p3, resultPt);
    EXPECT_NEAR(8, resultPt.x, 0.01);
    EXPECT_NEAR(5, resultPt.y, 0.01);
    EXPECT_EQ(res, LINES_INTERSECT_IN_SEGMENT);

    // no intersection
    p2.set(1, 2); p3.set(8, 6);
    resultPt.zero();
    res = CheckLinesIntersection(p0, p1, p2, p3, resultPt);
    EXPECT_TRUE(resultPt == vec2(0, 0));
    EXPECT_EQ(res, LINES_NO_INTERSECT);

    // out of segment intersection
    p2.set(1, 5); p3.set(10, 6);
    resultPt.zero();
    res = CheckLinesIntersection(p0, p1, p2, p3, resultPt);
    EXPECT_TRUE(resultPt == vec2(9.6896551, 5.9655172));
    EXPECT_EQ(res, LINES_INTERSECT_OUT_SEGMENT);
}
