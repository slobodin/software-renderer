/*
 * math_utils.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include "vec2.h"
#include "vec3.h"
#include "plane.h"

namespace math
{

//! Computes angle between two 2-vectors.
/*! \returns Angle in degrees. */
float AngleBetween(const vec2 &a, const vec2 &b);

//! Computes angle between two 3-vectors.
/*! \returns Angle in degrees. */
float AngleBetween(const vec3 &a, const vec3 &b);

//! Lines intersection types
enum LinesIntersectionType
{
    LINES_NO_INTERSECT,
    LINES_INTERSECT_IN_SEGMENT,
    LINES_INTERSECT_OUT_SEGMENT
};

//! This function checks whether the 2D lines intersects.
/*!
  * \param p1_1 First point of the first line.
  * \param p1_2 Second point of the first line.
  * \param p2_1 First point of the first line.
  * \param p2_2 Second point of the first line.
  * \param resultPoint If lines are intersect this point will contain result coords of intersection point
  * \return LINES_NO_INTERSECT No intersection.
  * \return LINES_INTERSECT_IN_SEGMENT Intersection in [p0, p1] segment.
  * \return LINES_INTERSECT_OUT_SEGMENT Intersection out of [p0, p1] segment.
  */
LinesIntersectionType CheckLinesIntersection(const vec2 &p1_1, const vec2 &p1_2,
                                             const vec2 &p2_1, const vec2 &p2_2,
                                             vec2 &resultPoint);

}

#endif // MATH_UTILS_H
