#ifndef AFFINETRANSFORM_H
#define AFFINETRANSFORM_H

#include "comm_pch.h"

#include "m33.h"
#include "vec3.h"

namespace math
{

//! M * x + v
class AffineTransform
{
    M33 m_M;
    vec3 m_v;
public:
    AffineTransform();
    AffineTransform(const M33 &M, const vec3 &v);
    AffineTransform(const M33 &M);
    AffineTransform(const vec3 &v);
    ~AffineTransform();

    void setv(const vec3 &v);
    void setm(const M33 &m);

    vec3 getv() const { return m_v; }
    M33 getm() const { return m_M; }

    void getHomogeneousMatrix() const;

    void transformPoint(vec3 &p) const;
};

}

#endif // AFFINETRANSFORM_H
