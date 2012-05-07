/*
 * test_plane.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include <gtest/gtest.h>

#include "plane.h"

using namespace math;

TEST(Plane, LineIntersection)
{
    Plane pl(vec3(0, 1, 0), vec3(0, 0, 0)); // plane
    vec3 p0(4, 4, 4), p1(5, -5, -4);        // line

    vec3 intersect;
    LinePlaneIntersectionType res = pl.checkLine(p0, p1, intersect);

    // intersection in segment
    EXPECT_EQ(LINE_PLANE_INTERSECT_IN_SEGMENT, res);
    EXPECT_NEAR(4.43, intersect.x, 0.1);
    EXPECT_NEAR(0, intersect.y, 0.1);
    EXPECT_NEAR(0.43, intersect.z, 0.1);

    // intersection out of segment
    p1.set(1, 1, 1);
    res = pl.checkLine(p0, p1, intersect);
    EXPECT_EQ(LINE_PLANE_INTERSECT_OUT_SEGMENT, res);
    EXPECT_NEAR(0, intersect.x, 0.1);
    EXPECT_NEAR(0, intersect.y, 0.1);
    EXPECT_NEAR(0, intersect.z, 0.1);

    // line lies on the plane
    intersect.zero();
    p0.set(0, 0, 0); p1.set(1, 0, 1);
    res = pl.checkLine(p0, p1, intersect);
    EXPECT_EQ(LINE_PLANE_INTERSECT_EVERYWHERE, res);
    EXPECT_NEAR(0, intersect.x, EPSILON_E6);
    EXPECT_NEAR(0, intersect.y, EPSILON_E6);
    EXPECT_NEAR(0, intersect.z, EPSILON_E6);

    // line and plane are parallel
    intersect.zero();
    p0.set(0, 2, 0); p1.set(1, 2, 1);
    res = pl.checkLine(p0, p1, intersect);
    EXPECT_EQ(LINE_PLANE_NO_INTERSECT, res);
    EXPECT_NEAR(0, intersect.x, EPSILON_E6);
    EXPECT_NEAR(0, intersect.y, EPSILON_E6);
    EXPECT_NEAR(0, intersect.z, EPSILON_E6);
}
