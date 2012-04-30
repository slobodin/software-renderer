/*
 * m33.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef M33_H
#define M33_H

#include "comm_pch.h"

#include "vec3.h"

namespace math
{

//! Row-column 3x3 Matrix.
/*!
  * (a00, a01, a02)
  * (a10, a11, a12)
  * (a20, a21, a22)
  */
struct M33
{
    double x[3][3];

    //! Identity matrix
    M33();
    M33(const double src[3][3]);
    M33(double xx, double xy, double xz,
        double yx, double yy, double yz,
        double zx, double zy, double zz);

    M33 &operator= (const M33 &a);
    M33 &operator+= (const M33 &a);
    M33 &operator-= (const M33 &a);
    M33 &operator*= (const M33 &a);
    M33 &operator*= (const double s);
    M33 &operator/= (const double s);

    M33 &invert();
    M33 &transpose();
    double determinant() const;

    static M33 getScaleMatrix(const vec3 &vect);
    //! angle in degrees
    static M33 getRotateXMatrix(const double angle);
    static M33 getRotateYMatrix(const double angle);
    static M33 getRotateZMatrix(const double angle);
    static M33 getRotateYawPitchRollMatrix(const double yaw,
                                            const double pitch,
                                            const double roll);

    friend M33 operator+ (const M33 &a, const M33 &b);
    friend M33 operator- (const M33 &a, const M33 &b);
    friend M33 operator* (const M33 &a, const M33 &b);
    friend M33 operator* (const M33 &a, const double s);
    friend M33 operator* (const double s, const M33 &a);

    /** |1 2 3|   ( 1 )
        |4 5 6| * ( 2 )
        |7 8 9|   ( 3 ) */
    friend vec3 operator* (const M33 &a, const vec3 &b);
};

}

#endif // M22_H
