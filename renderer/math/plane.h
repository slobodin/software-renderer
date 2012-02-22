#ifndef PLANE_H
#define PLANE_H

#include "comm_pch.h"

#include "vec3.h"

namespace math
{

//! ax + by + cz + d = 0
/** m_normal(a, b, c)
    m_d == d */
class Plane
{
    vec3 m_normal;
    double m_d;
public:
    //! build from normal vector and distance
    Plane(const vec3 &n, const double d);
    //! build from plane equation
    Plane(const double a, const double b, const double c, const double d);
    //! build from 3 points
    Plane(const vec3 &p0, const vec3 &p1, const vec3 &p2);
};

}

#endif // PLANE_H
