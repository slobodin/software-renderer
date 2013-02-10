/*
 * math_utils.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "stdafx.h"

#include "math_utils.h"

namespace math
{

float AngleBetween(const vec2 &a, const vec2 &b)
{
    float dotProd = a.dotProduct(b);
    float cosine = dotProd / (a.length() * b.length());

    return RadToDeg(acos(cosine));
}

float AngleBetween(const vec3 &a, const vec3 &b)
{
    float dotProd = a.dotProduct(b);
    float cosine = dotProd / (a.length() * b.length());

    return RadToDeg(acos(cosine));
}

LinesIntersectionType CheckLinesIntersection(const vec2 &p1_1, const vec2 &p1_2,
                                             const vec2 &p2_1, const vec2 &p2_2,
                                             vec2 &resultPoint)
{
    const vec2 line1dir = p1_2 - p1_1;
    const vec2 line2dir = p2_2 - p2_1;

    float det = line1dir.x * line2dir.y - line1dir.y * line2dir.x;
    if (DCMP(det, 0.0))
        // lines are either intersect or match
        return LINES_NO_INTERSECT;

    float t1 = (line2dir.x * (p1_1.y - p2_1.y) - line2dir.y * (p1_1.x - p2_1.x)) / det;
    float t2 = (line1dir.x * (p1_1.y - p2_1.y) - line1dir.y * (p1_1.x - p2_1.x)) / det;

    resultPoint.x = p1_1.x + line1dir.x * t1;
    resultPoint.y = p1_1.y + line1dir.y * t1;

    if (t1 >= 0.0 && t1 <= 1.0 && t2 >= 0.0 && t2 <= 1.0)
        return LINES_INTERSECT_IN_SEGMENT;
    else
        return LINES_INTERSECT_OUT_SEGMENT;
}

}
