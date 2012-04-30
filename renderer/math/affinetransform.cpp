/*
 * affinetransform.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "affinetransform.h"

namespace math
{

AffineTransform::AffineTransform()
{
}

AffineTransform::AffineTransform(const M33 &M, const vec3 &v)
    : m_M(M),
      m_v(v)
{
}

AffineTransform::AffineTransform(const M33 &M)
    : m_M(M)
{
}

AffineTransform::AffineTransform(const vec3 &v)
    : m_v(v)
{
}


AffineTransform::~AffineTransform()
{
}

void AffineTransform::setv(const vec3 &v)
{
    m_v = v;
}

void AffineTransform::setm(const M33 &m)
{
    m_M = m;
}

M44 AffineTransform::getHomogeneousMatrix() const
{

}

void AffineTransform::transformPoint(vec3 &p) const
{
    // FIXME: may be wrong.
    p += m_v;
    p = p * m_M;
}

}
