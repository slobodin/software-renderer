/*
 * m22.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef M22_H
#define M22_H

#include "comm_pch.h"

#include "vec2.h"

namespace math
{

//! Matrix 2 x 2
struct M22
{
    double x[4];

    //! Identity matrix
    M22();
    M22(const double src[4]);
    M22(double xx, double xy, double yx, double yy);

    M22 &operator+= (const M22 &a);
    M22 &operator-= (const M22 &a);
    M22 &operator*= (const M22 &a);
    M22 &operator*= (const double s);
    M22 &operator/= (const double s);
    double &operator[] (const int index) { return x[index]; }
    double operator[] (const int index) const { return x[index]; }

    M22 &invert();
    M22 &transpose();
    double determinant() const;
    double *getPointer() { return x; }

    friend M22 operator+ (const M22 &a, const M22 &b);
    friend M22 operator- (const M22 &a, const M22&b);
    friend M22 operator* (const M22 &a, const M22 &b);
    friend M22 operator* (const M22 &a, const double s);
    friend M22 operator* (const double s, const M22 &);

    /** |1 2| * ( 1 )
        |3 4|   ( 2 ) */
    friend vec2 operator* (const M22 &a, const vec2 &b);
};

inline M22::M22()
{
    x[0] = x[3] = 1.0;
    x[1] = x[2] = 0.0;
}

inline M22::M22(double xx, double xy, double yx, double yy)
{
    x[0] = xx;
    x[1] = xy;
    x[2] = yx;
    x[3] = yy;
}

inline M22::M22(const double src[4])
{
    memcpy(x, src, 4 * sizeof(double));
}

inline M22 &M22::operator+= (const M22 &a)
{
    x[0] += a.x[0];
    x[1] += a.x[1];
    x[2] += a.x[2];
    x[3] += a.x[3];
    return *this;
}

inline M22 &M22::operator-= (const M22 &a)
{
    x[0] -= a.x[0];
    x[1] -= a.x[1];
    x[2] -= a.x[2];
    x[3] -= a.x[3];
    return *this;
}

inline M22 &M22::operator*= (const M22 &a)
{
    M22 temp = *this;

    x[0] = temp.x[0] * a.x[0] + temp.x[1] * a.x[2];
    x[1] = temp.x[0] * a.x[1] + temp.x[1] * a.x[3];
    x[2] = temp.x[2] * a.x[0] + temp.x[3] * a.x[2];
    x[3] = temp.x[2] * a.x[1] + temp.x[3] * a.x[3];
    return *this;
}

inline M22 &M22::operator*= (const double s)
{
    x[0] *= s;
    x[1] *= s;
    x[2] *= s;
    x[3] *= s;
    return *this;
}

inline M22 &M22::operator/= (const double s)
{
    assert(s != 0.0);

    x[0] /= s;
    x[1] /= s;
    x[2] /= s;
    x[3] /= s;
    return *this;
}

inline M22 &M22::invert()
{
    double d = determinant();
    assert(d != 0.0);
    M22 temp;

    temp.x[0] = x[3] / d;
    temp.x[1] = -x[1] / d;
    temp.x[2] = -x[2] / d;
    temp.x[3] = x[0] / d;
    return *this = temp;
}

inline M22 &M22::transpose()
{
    M22 temp;
    temp.x[0] = x[0];
    temp.x[1] = x[2];
    temp.x[2] = x[1];
    temp.x[3] = x[3];
    return *this = temp;
}

inline double M22::determinant() const
{
    return (x[0] * x[3] - x[1] * x[2]);
}

inline M22 operator+ (const M22 &a, const M22 &b)
{
    M22 res;
    res.x[0] = a.x[0] + b.x[0];
    res.x[1] = a.x[1] + b.x[1];
    res.x[2] = a.x[2] + b.x[2];
    res.x[3] = a.x[3] + b.x[3];
    return res;
}

inline M22 operator- (const M22 &a, const M22 &b)
{
    M22 res;
    res.x[0] = a.x[0] - b.x[0];
    res.x[1] = a.x[1] - b.x[1];
    res.x[2] = a.x[2] - b.x[2];
    res.x[3] = a.x[3] - b.x[3];
    return res;
}

inline M22 operator* (const M22 &a, const M22 &b)
{
    M22 res;
    res.x[0] = a.x[0] * b.x[0] + a.x[1] * b.x[2];
    res.x[1] = a.x[0] * b.x[1] + a.x[1] * b.x[3];
    res.x[2] = a.x[2] * b.x[0] + a.x[3] * b.x[2];
    res.x[3] = a.x[2] * b.x[1] + a.x[3] * b.x[3];
    return res;
}

inline M22 operator* (const M22 &a, const double s)
{
    M22 res(a);
    return res *= s;
}

inline M22 operator* (const double s, const M22 &b)
{
    M22 res(b);
    return res *= s;
}

inline vec2 operator* (const M22 &a, const vec2 &b)
{
    return vec2(a.x[0] * b.x + a.x [1] * b.y,
                a.x[2] * b.x + a.x [3] * b.y );
}

}

#endif // M22_H
