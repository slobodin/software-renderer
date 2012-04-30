/*
 * math_utils.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include "comm_pch.h"

#include "vec2.h"
#include "vec3.h"
#include "plane.h"

namespace math
{

//! Computes angle between two 2-vectors.
/*! \returns angle in degrees. */
double AngleBetween(const vec2 &a, const vec2 &b);

//! Computes angle between two 3-vectors.
/*! \returns angle in degrees. */
double AngleBetween(const vec3 &a, const vec3 &b);

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

//! This function checks whether the 3D lines intersects.
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
LinesIntersectionType CheckLinesIntersection(const vec3 &p1_1, const vec3 &p1_2,
                                             const vec3 &p2_1, const vec3 &p2_2,
                                             vec3 &resultPoint);

//! Line plane intersection types
enum LinePlaneIntersectionType
{
    LINE_PLANE_NO_INTERSECT,
    LINE_PLANE_INTERSECT_IN_SEGMENT,
    LINE_PLANE_INTERSECT_OUT_SEGMENT,
    LINE_PLANE_INTERSECT_EVERYWHERE
};

//! This function checks whether the line and plane intersects.
/*!
  * \param p0 First point of the line.
  * \param p1 Second point of the line.
  * \param plane Plane.
  * \param resultPoint Output intersection point.
  * \return LINE_PLANE_NO_INTERSECT No intersection.
  * \return LINE_PLANE_INTERSECT_IN_SEGMENT Intersection in segment [p0, p1].
  * \return LINES_INTERSECT_OUT_SEGMENT Intersection out of segment [p0, p1].
  * \return LINE_PLANE_INTERSECT_EVERYWHERE Line lies on plane.
  */
LinePlaneIntersectionType CheckLinePlaneIntersection(const vec3 &p0, const vec3 &p1,
                                                     const Plane &plane, vec3 &resultPoint);

}

#endif // MATH_UTILS_H
