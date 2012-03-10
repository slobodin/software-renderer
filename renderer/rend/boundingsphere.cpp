/*
 * boundingsphere.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "boundingsphere.h"

namespace rend
{

BoundingSphere::BoundingSphere()
    : m_radius(-1.0)
{
}

BoundingSphere::BoundingSphere(const vector<math::vec3> &vertices)
    : m_radius(-1.0)
{
    calculate(vertices);
}

BoundingSphere::~BoundingSphere()
{
}

void BoundingSphere::calculate(const vector<math::vec3> &vertices)
{
    if (vertices.empty())
        return;

    for (unsigned i = 0; i < vertices.size(); i++)
        m_centerPoint += vertices[i];

    m_centerPoint /= vertices.size();

    m_radius = (m_centerPoint - vertices[0]).length();
    for (unsigned i = 1; i < vertices.size(); i++)
    {
        double currR = (m_centerPoint - vertices[1]).length();

        if (currR > m_radius)
            m_radius = currR;
    }
}

}
