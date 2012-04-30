/*
 * m33.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "m33.h"

#include <boost/foreach.hpp>

namespace math
{

M33::M33()
{
    memset(&x[0], 0, sizeof(double) * 3 * 3);
    x[0][0] = x[1][1] = x[2][2] = 1.0;
}

M33::M33(const double (&src)[3][3])
{
    memcpy(x, src, 3 * 3 * sizeof(double));
}

M33::M33(double a00, double a01, double a02,
         double a10, double a11, double a12,
         double a20, double a21, double a22)
{
    x[0][0] = a00;
    x[0][1] = a01;
    x[0][2] = a02;
    x[1][0] = a10;
    x[1][1] = a11;
    x[1][2] = a12;
    x[2][0] = a20;
    x[2][1] = a21;
    x[2][2] = a22;
}

M33 &M33::operator+= (const M33 &a)
{
    x[0][0] += a.x[0][0];
    x[0][1] += a.x[0][1];
    x[0][2] += a.x[0][2];
    x[1][0] += a.x[1][0];
    x[1][1] += a.x[1][1];
    x[1][2] += a.x[1][2];
    x[2][0] += a.x[2][0];
    x[2][1] += a.x[2][1];
    x[2][2] += a.x[2][2];
    return *this;
}

M33 &M33::operator-= (const M33 &a)
{
    x[0][0] -= a.x[0][0];
    x[0][1] -= a.x[0][1];
    x[0][2] -= a.x[0][2];
    x[1][0] -= a.x[1][0];
    x[1][1] -= a.x[1][1];
    x[1][2] -= a.x[1][2];
    x[2][0] -= a.x[2][0];
    x[2][1] -= a.x[2][1];
    x[2][2] -= a.x[2][2];
    return *this;
}

M33 &M33::operator*= (const M33 &a)
{
    M33 temp = *this;

    x[0][0] = temp.x[0][0] * a.x[0][0] + temp.x[0][1] * a.x[1][0] + temp.x[0][2] * a.x[2][0];
    x[0][1] = temp.x[0][0] * a.x[0][1] + temp.x[0][1] * a.x[1][1] + temp.x[0][2] * a.x[2][1];
    x[0][2] = temp.x[0][0] * a.x[0][2] + temp.x[0][1] * a.x[1][2] + temp.x[0][2] * a.x[2][2];
    x[1][0] = temp.x[1][0] * a.x[0][0] + temp.x[1][1] * a.x[1][0] + temp.x[1][2] * a.x[2][0];
    x[1][1] = temp.x[1][0] * a.x[0][1] + temp.x[1][1] * a.x[1][1] + temp.x[1][2] * a.x[2][1];
    x[1][2] = temp.x[1][0] * a.x[0][2] + temp.x[1][1] * a.x[1][2] + temp.x[1][2] * a.x[2][2];
    x[2][0] = temp.x[2][0] * a.x[0][0] + temp.x[2][1] * a.x[1][0] + temp.x[2][2] * a.x[2][0];
    x[2][1] = temp.x[2][0] * a.x[0][1] + temp.x[2][1] * a.x[1][1] + temp.x[2][2] * a.x[2][1];
    x[2][2] = temp.x[2][0] * a.x[0][2] + temp.x[2][1] * a.x[1][2] + temp.x[2][2] * a.x[2][2];

    return *this;
}

M33 &M33::operator*= (double s)
{
    BOOST_FOREACH (double (&row)[3], x)
        BOOST_FOREACH (double &el, row)
            el *= s;

    return *this;
}

M33 &M33::operator/= (double s)
{
    assert(!DCMP(s, 0.0));

    BOOST_FOREACH (double (&row)[3], x)
        BOOST_FOREACH (double &el, row)
            el /= s;

    return *this;
}

bool M33::operator== (const M33 &a) const
{
    return DCMP(x[0][0], a.x[0][0]) && DCMP(x[0][1], a.x[0][1]) && DCMP(x[0][2], a.x[0][2]) &&
           DCMP(x[1][0], a.x[1][0]) && DCMP(x[1][1], a.x[1][1]) && DCMP(x[1][2], a.x[1][2]) &&
           DCMP(x[2][0], a.x[2][0]) && DCMP(x[2][1], a.x[2][1]) && DCMP(x[2][2], a.x[2][2]);
}

M33 &M33::invert()
{
    double det = determinant();
    assert(!DCMP(det, 0.0));

    M33 res;
    res.x[0][0] = (x[1][1] * x[2][2] - x[1][2] * x[2][1]) / det;
    res.x[0][1] = (x[0][2] * x[2][1] - x[0][1] * x[2][2]) / det;
    res.x[0][2] = (x[0][1] * x[1][2] - x[0][2] * x[1][1]) / det;
    res.x[1][0] = (x[1][2] * x[2][0] - x[1][0] * x[2][2]) / det;
    res.x[1][1] = (x[0][0] * x[2][2] - x[0][2] * x[2][0]) / det;
    res.x[1][2] = (x[0][2] * x[1][0] - x[0][0] * x[1][2]) / det;
    res.x[2][0] = (x[1][0] * x[2][1] - x[1][1] * x[2][0]) / det;
    res.x[2][1] = (x[0][1] * x[2][0] - x[0][0] * x[2][1]) / det;
    res.x[2][2] = (x[0][0] * x[1][1] - x[0][1] * x[1][0]) / det;

    return *this = res;
}

M33 &M33::transpose()
{
    M33 res;

    res.x[0][0] = x[0][0];
    res.x[0][1] = x[1][0];
    res.x[0][2] = x[2][0];
    res.x[1][0] = x[0][1];
    res.x[1][1] = x[1][1];
    res.x[1][2] = x[2][1];
    res.x[2][0] = x[0][2];
    res.x[2][1] = x[1][2];
    res.x[2][2] = x[2][2];

    return *this = res;
}

double M33::determinant() const
{
    return (x[0][0] * (x[1][1] * x[2][2] - x[1][2] * x[2][1]) -
            x[0][1] * (x[1][0] * x[2][2] - x[1][2] * x[2][0]) +
            x[0][2] * (x[1][0] * x[2][1] - x[1][1] * x[2][0]));
}

M33 M33::getScaleMatrix(const vec3 &vect)
{
    M33 A;

    A.x[0][0] = vect.x;
    A.x[1][1] = vect.y;
    A.x[2][2] = vect.z;

    return A;
}

M33 M33::getRotateXMatrix(double angle, bool rads)
{
    M33 A;

    double cosinus = rads ? cos(angle) : cos(DegToRad(angle));
    double sinus = rads ? sin(angle) : sin(DegToRad(angle));

    A.x[1][1] = cosinus;
    A.x[1][2] = sinus;
    A.x[2][1] = -sinus;
    A.x[2][2] = cosinus;

    return A;
}

M33 M33::getRotateYMatrix(double angle, bool rads)
{
    M33 A;

    double cosinus = rads ? cos(angle) : cos(DegToRad(angle));
    double sinus = rads ? sin(angle) : sin(DegToRad(angle));

    A.x[0][0] = cosinus;
    A.x[0][2] = -sinus;
    A.x[2][0] = sinus;
    A.x[2][2] = cosinus;

    return A;
}

M33 M33::getRotateZMatrix(double angle, bool rads)
{
    M33 A;

    double cosinus = rads ? cos(angle) : cos(DegToRad(angle));
    double sinus = rads ? sin(angle) : sin(DegToRad(angle));

    A.x[0][0] = cosinus;
    A.x[0][1] = sinus;
    A.x[1][0] = -sinus;
    A.x[1][1] = cosinus;

    return A;
}

M33 M33::getRotateYawPitchRollMatrix(double yaw, double pitch, double roll, bool rads)
{
    return getRotateYMatrix(yaw, rads)
            * getRotateZMatrix(roll, rads)
            * getRotateXMatrix(pitch, rads);
}

M33 operator+ (const M33 &a, const M33 &b)
{
    M33 res;

    res.x[0][0] = a.x[0][0] + b.x[0][0];
    res.x[0][1] = a.x[0][1] + b.x[0][1];
    res.x[0][2] = a.x[0][2] + b.x[0][2];
    res.x[1][0] = a.x[1][0] + b.x[1][0];
    res.x[1][1] = a.x[1][1] + b.x[1][1];
    res.x[1][2] = a.x[1][2] + b.x[1][2];
    res.x[2][0] = a.x[2][0] + b.x[2][0];
    res.x[2][1] = a.x[2][1] + b.x[2][1];
    res.x[2][2] = a.x[2][2] + b.x[2][2];

    return res;
}

M33 operator- (const M33 &a, const M33 &b)
{
    M33 res;

    res.x[0][0] = a.x[0][0] - b.x[0][0];
    res.x[0][1] = a.x[0][1] - b.x[0][1];
    res.x[0][2] = a.x[0][2] - b.x[0][2];
    res.x[1][0] = a.x[1][0] - b.x[1][0];
    res.x[1][1] = a.x[1][1] - b.x[1][1];
    res.x[1][2] = a.x[1][2] - b.x[1][2];
    res.x[2][0] = a.x[2][0] - b.x[2][0];
    res.x[2][1] = a.x[2][1] - b.x[2][1];
    res.x[2][2] = a.x[2][2] - b.x[2][2];

    return res;
}

M33 operator* (const M33 &a, const M33 &b)
{
    M33 c = a;

    c.x[0][0] = a.x[0][0] * b.x[0][0] + a.x[0][1] * b.x[1][0] + a.x[0][2] * b.x[2][0];
    c.x[0][1] = a.x[0][0] * b.x[0][1] + a.x[0][1] * b.x[1][1] + a.x[0][2] * b.x[2][1];
    c.x[0][2] = a.x[0][0] * b.x[0][2] + a.x[0][1] * b.x[1][2] + a.x[0][2] * b.x[2][2];
    c.x[1][0] = a.x[1][0] * b.x[0][0] + a.x[1][1] * b.x[1][0] + a.x[1][2] * b.x[2][0];
    c.x[1][1] = a.x[1][0] * b.x[0][1] + a.x[1][1] * b.x[1][1] + a.x[1][2] * b.x[2][1];
    c.x[1][2] = a.x[1][0] * b.x[0][2] + a.x[1][1] * b.x[1][2] + a.x[1][2] * b.x[2][2];
    c.x[2][0] = a.x[2][0] * b.x[0][0] + a.x[2][1] * b.x[1][0] + a.x[2][2] * b.x[2][0];
    c.x[2][1] = a.x[2][0] * b.x[0][1] + a.x[2][1] * b.x[1][1] + a.x[2][2] * b.x[2][1];
    c.x[2][2] = a.x[2][0] * b.x[0][2] + a.x[2][1] * b.x[1][2] + a.x[2][2] * b.x[2][2];

    return c;
}

M33 operator* (const M33 &a, double s)
{
    M33 res = a;

    return res *= s;
}

M33 operator* (double s, const M33 &b)
{
    M33 res = b;

    return res *= s;
}

vec3 operator* (const vec3 &v, const M33 &a)
{
    return vec3(a.x[0][0] * v.x + a.x[1][0] * v.y + a.x[2][0] * v.z,
                a.x[0][1] * v.x + a.x[1][1] * v.y + a.x[2][1] * v.z,
                a.x[0][2] * v.x + a.x[1][2] * v.y + a.x[2][2] * v.z);
}

}
