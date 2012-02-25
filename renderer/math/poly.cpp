#include "poly.h"

namespace math
{

Triangle::Triangle()
{
}

Triangle::Triangle(const vec3 *arr)
{
    if (!arr)
    {
        *syslog << "Trying to initialize triangle with an empty array" << logdebug;
        return;
    }

    m_verts[0] = arr[0];
    m_verts[1] = arr[1];
    m_verts[2] = arr[2];
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

}
