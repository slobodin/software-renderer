/*
 * math_utils.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "math_utils.h"
#include <boost/numeric/interval.hpp>

namespace math
{

static const boost::numeric::interval<double> ZERO_ONE_INTERVAL(0.0, 1.0);

double AngleBetween(const vec2 &a, const vec2 &b)
{
    double dotProd = a.dotProduct(b);
    double cosine = dotProd / (a.length() * b.length());

    return RadToDeg(acos(cosine));
}

double AngleBetween(const vec3 &a, const vec3 &b)
{
    double dotProd = a.dotProduct(b);
    double cosine = dotProd / (a.length() * b.length());

    return RadToDeg(acos(cosine));
}

LinesIntersectionType CheckLinesIntersection(const vec2 &p1_1, const vec2 &p1_2,
                                             const vec2 &p2_1, const vec2 &p2_2,
                                             vec2 &resultPoint)
{
    // TODO
    vec2 line1dir = p1_2 - p1_1;
    vec2 line2dir = p2_2 - p2_1;


//    vec2 dir = p1 - p0;
}

LinesIntersectionType CheckLinesIntersection(const vec3 &p1_1, const vec3 &p1_2,
                                             const vec3 &p2_1, const vec3 &p2_2,
                                             vec3 &resultPoint)
{
    // TODO
}

LinePlaneIntersectionType CheckLinePlaneIntersection(const vec3 &p0, const vec3 &p1,
                                                     const Plane &plane, vec3 &resultPoint)
{
    // TODO
}

}
