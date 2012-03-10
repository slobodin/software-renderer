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

}
