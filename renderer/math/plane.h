/*
 * plane.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef PLANE_H
#define PLANE_H

#include "comm_pch.h"

#include "vec3.h"

namespace math
{

//! Point plane relation types.
enum PointPlaneRelation
{
    POINT_IN_PLANE,             /*!< Point lies on plane. */
    POINT_IN_FRONT_OF_PLANE,    /*!< Point in front of the plane (normal vector looks to the "front"). */
    POINT_IN_BACK_OF_PLANE      /*!< Point in back of the plane. */
};

//! Line plane intersection types.
enum LinePlaneIntersectionType
{
    LINE_PLANE_NO_INTERSECT,            /*!< No line-plane intersection. */
    LINE_PLANE_INTERSECT_IN_SEGMENT,    /*!< Line and plane intersects in segment [p0, p1]. */
    LINE_PLANE_INTERSECT_OUT_SEGMENT,   /*!< Line and plane intersects out of segment [p0, p1]. */
    LINE_PLANE_INTERSECT_EVERYWHERE     /*!< Line lies on plane. */
};

//! Plane in 3D space.
/*!
  * With equation Ax + By + Cz + D = 0.
  */
class Plane
{
    //! Plane normal(A, B, C).
    vec3 m_normal;
    //! Distance from origin D.
    double m_d;

public:
    //! Build plane from normal vector and distance.
    Plane(const vec3 &n, const double d);
    //! Build plane from normal vector and point on plane.
    Plane(const vec3 &n, const vec3 &p);
    //! Build from plane equation.
    Plane(const double a, const double b, const double c, const double d);
    //! Build plane with 3 points.
    Plane(const vec3 &p0, const vec3 &p1, const vec3 &p2);

    const vec3 &normal() const { return m_normal; }
    double distance() const { return m_d; }

    //! Check point position relative to the plane.
    /*!
      * \param p Checked point.
      * \return Point plane relation.
      */
    PointPlaneRelation checkPoint(const vec3 &p) const;

    //! This function checks whether the line and plane intersects.
    /*!
      * \param p0 First point of the line.
      * \param p1 Second point of the line.
      * \param resultPoint Output intersection point.
      * \returns Line-plane intersection type.
      */
    LinePlaneIntersectionType checkLine(const vec3 &p0, const vec3 &p1,
                                        vec3 &resultPoint);
};

}

#endif // PLANE_H
