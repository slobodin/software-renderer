/*
 * affinetransform.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef AFFINETRANSFORM_H
#define AFFINETRANSFORM_H

#include "comm_pch.h"

#include "m33.h"
#include "m44.h"
#include "vec3.h"

namespace math
{

//! Affine transformation.
/*!
  * M * x + v,
  * where M is scale and\or rotation matrix,
  * v - translation vector
  */
class AffineTransform
{
    //! Matrix.
    M33 m_M;
    //! Vector
    vec3 m_v;

    // TODO: maybe full 4x4 matrix?

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

    M44 getHomogeneousMatrix() const;

    void transformPoint(vec3 &p) const;
};

}

#endif // AFFINETRANSFORM_H
