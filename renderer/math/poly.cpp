#include "poly.h"

namespace math
{

Triangle::Triangle(WindingOrder wo)
    : m_windingOrder(wo)
{
}

Triangle::Triangle(const vec3 *arr, WindingOrder wo)
    : m_windingOrder(wo)
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

const vec3 &Triangle::v(const size_t ind) const
{
    if (ind > 2)
    {
        throw common::OutOfRangeException("Bad index passed to triangle->v()");
    }

    return m_verts[ind];
}

vec3 &Triangle::v(const size_t ind)
{
    if (ind > 2)
    {
        throw common::OutOfRangeException("Bad index passed to triangle->v()");
    }

    return m_verts[ind];
}

void Triangle::computeNormal()
{
    vec3 p1 = (m_verts[1] - m_verts[0]).normalize();
    vec3 p2 = (m_verts[2] - m_verts[0]).normalize();

    if (m_windingOrder == WO_CW)
        m_normal = p1.crossProduct(p2);
    else if (m_windingOrder == WO_CCW)
        m_normal = p2.crossProduct(p1);
    else
        throw std::exception();

    m_normal.normalize();
}

}
