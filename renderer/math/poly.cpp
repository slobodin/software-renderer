/*
 * poly.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "poly.h"

namespace math
{

Triangle::Triangle(WindingOrder wo, SideType st)
    : m_windingOrder(wo),
      m_sideType(st)
{
}

Triangle::Triangle(const vertex *arr, WindingOrder wo, SideType st)
    : m_windingOrder(wo),
      m_sideType(st)
{
    if (!arr)
    {
        *syslog << "Trying to initialize triangle with an empty array" << logdebug;
        return;
    }

    m_verts[0] = arr[0];
    m_verts[1] = arr[1];
    m_verts[2] = arr[2];

    computeNormal();
}

const vertex &Triangle::v(const size_t ind) const
{
    if (ind > 2)
    {
        throw common::OutOfRangeException("Bad index passed to triangle->v()");
    }

    return m_verts[ind];
}

vertex &Triangle::v(const size_t ind)
{
    if (ind > 2)
    {
        throw common::OutOfRangeException("Bad index passed to triangle->v()");
    }

    return m_verts[ind];
}

vector<vec3> Triangle::points() const
{
    vector<vec3> res(3);
    res[0] = m_verts[0].p;
    res[1] = m_verts[1].p;
    res[2] = m_verts[2].p;

    return res;
}

vector<vec3> Triangle::normals() const
{
    vector<vec3> res(3);
    res[0] = m_verts[0].n;
    res[1] = m_verts[1].n;
    res[2] = m_verts[2].n;

    return res;
}

vector<vec2> Triangle::uvs() const
{
    vector<vec2> res(3);
    res[0] = m_verts[0].t;
    res[1] = m_verts[1].t;
    res[2] = m_verts[2].t;

    return res;
}

void Triangle::computeNormal()
{
    vec3 p1, p2;

    if (m_windingOrder == WO_CW)
    {
        p1.set((m_verts[1].p - m_verts[0].p).normalize());
        p2.set((m_verts[2].p - m_verts[0].p).normalize());
    }
    else if (m_windingOrder == WO_CCW)
    {
        p1.set((m_verts[0].p - m_verts[1].p).normalize());
        p2.set((m_verts[2].p - m_verts[1].p).normalize());
    }
    else
        throw std::exception();

    m_normal = p1.crossProduct(p2);
    m_normal.normalize();
}

bool ZCompareAvg(const math::Triangle &t1, const math::Triangle &t2)
{
    double avgz = 0.33333 * (t1.m_verts[0].p.z + t1.m_verts[1].p.z + t1.m_verts[2].p.z);
    double avgotherz = 0.33333 * (t2.m_verts[0].p.z + t2.m_verts[1].p.z + t2.m_verts[2].p.z);

    if (avgz < avgotherz)
        return true;

    return false;
}

bool ZCompareMin(const Triangle &t1, const Triangle &t2)
{
    vector<vec3> points = t1.points();
    double minz1 = (*std::min_element(points.begin(), points.end(), comparez<double>)).z;

    points = t2.points();
    double minz2 = (*std::min_element(points.begin(), points.end(), comparez<double>)).z;

    if (minz1 < minz2)
        return true;

    return false;
}

bool ZCompareMax(const Triangle &t1, const Triangle &t2)
{
    vector<vec3> points = t1.points();
    double minz1 = (*std::max_element(points.begin(), points.end(), comparez<double>)).z;

    points = t2.points();
    double minz2 = (*std::max_element(points.begin(), points.end(), comparez<double>)).z;

    if (minz1 < minz2)
        return true;

    return false;
}

}
