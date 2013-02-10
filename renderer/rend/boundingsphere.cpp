/*
 * boundingsphere.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "stdafx.h"

#include "boundingsphere.h"

namespace rend
{

BoundingSphere::BoundingSphere()
    : m_radius(-1.0)
{
}

BoundingSphere::BoundingSphere(const std::vector<math::vec3> &vertices)
    : m_radius(-1.0)
{
    calculate(vertices);
}

BoundingSphere::~BoundingSphere()
{
}

void BoundingSphere::calculate(const std::vector<math::vec3> &vertices)
{
    if (vertices.empty())
        return;

    for (unsigned i = 0; i < vertices.size(); i++)
        m_centerPoint += vertices[i];

    m_centerPoint /= vertices.size();

    m_radius = (m_centerPoint - vertices[0]).length();
    for (unsigned i = 1; i < vertices.size(); i++)
    {
        float currR = (m_centerPoint - vertices[i]).length();

        if (currR > m_radius)
            m_radius = currR;
    }
}

}
