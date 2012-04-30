/*
 * plane.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "plane.h"

namespace math
{

Plane::Plane(const vec3 &n, const double d)
    : m_normal(n),
      m_d(d)
{
    m_normal.normalize();
}

Plane::Plane(const double a, const double b, const double c, const double d)
{
    m_normal.set(a, b, c);
    m_normal.normalize();
    m_d = d;
}

Plane::Plane(const vec3 &p0, const vec3 &p1, const vec3 &p2)
{
    m_normal = (p1 - p0).crossProduct(p2 - p0);
    m_normal.normalize();

    vec3 t = p0;
    m_d = t.dotProduct(m_normal);
}

PointPlaneRelation Plane::checkPoint(const vec3 &p) const
{
    // TODO
}

}
