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

//! Point plane relation types
enum PointPlaneRelation
{
    POINT_IN_PLANE,             /*!< Point lies on plane. */
    POINT_IN_FRONT_OF_PLANE,    /*!< Point in front of the plane. */
    POINT_IN_BACK_OF_PLANE      /*!< Point in back of the plane. */
};

//! Plane in 3D space
/*!
 * From equation Ax + By + Cz + D = 0
 */
class Plane
{
    //! Plane normal(A, B, C)
    vec3 m_normal;
    //! Distance from origin
    double m_d;

public:
    //! Build plane from normal vector and distance.
    Plane(const vec3 &n, const double d);
    //! Build from plane equation.
    Plane(const double a, const double b, const double c, const double d);
    //! Build plane with 3 points.
    Plane(const vec3 &p0, const vec3 &p1, const vec3 &p2);

    //! Check point position relative to the plane.
    /*!
      * \param p Checked point.
      * \return Point plane relation.
      */
    PointPlaneRelation checkPoint(const vec3 &p) const;
};

}

#endif // PLANE_H
