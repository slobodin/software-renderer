/*
 * plane.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "plane.h"

#include <boost/numeric/interval.hpp>

namespace math
{

static const boost::numeric::interval<float> ZERO_ONE_INTERVAL(0.0, 1.0);

Plane::Plane(const vec3 &n, float d)
    : m_normal(n),
      m_d(d)
{
    m_normal.normalize();
}

Plane::Plane(const vec3 &n, const vec3 &p)
    : m_normal(n)
{
    m_normal.normalize();
    m_d = -m_normal.x * p.x - m_normal.y * p.y - m_normal.z * p.z;
}

Plane::Plane(float a, float b, float c, float d)
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
    float dot = m_normal.dotProduct(p) + m_d;    // signed dist to the point
    if (dot > EPSILON_E3)
        return POINT_IN_FRONT_OF_PLANE;
    if (dot < -EPSILON_E3)
        return POINT_IN_BACK_OF_PLANE;

    return POINT_IN_PLANE;
}

LinePlaneIntersectionType Plane::checkLine(const vec3 &p0, const vec3 &p1,
                                           vec3 &resultPoint)
{
    const vec3 linedir = p1 - p0;
    float dotProd = linedir.dotProduct(m_normal);

    if (DCMP(dotProd, 0.0))
    {
        // lies or parallel

        if (checkPoint(p0) == POINT_IN_PLANE)
            // line lies on plane
            return LINE_PLANE_INTERSECT_EVERYWHERE;
        else
            // line and plane are parallel
            return LINE_PLANE_NO_INTERSECT;
    }

    float t = -(m_normal.x * p0.x +
                m_normal.y * p0.y +
                m_normal.z * p0.z +
                m_d) / dotProd;

    resultPoint.x = p0.x + linedir.x * t;
    resultPoint.y = p0.y + linedir.y * t;
    resultPoint.z = p0.z + linedir.z * t;

    if (boost::numeric::in(t, ZERO_ONE_INTERVAL))
        return LINE_PLANE_INTERSECT_IN_SEGMENT;
    else
        return LINE_PLANE_INTERSECT_OUT_SEGMENT;
}

}
