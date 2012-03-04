#include "m33.h"

namespace math
{

M33::M33()
{
    x[0][0] = x[1][1] = x[2][2] = 1.0;
    x[0][1] = x[0][2] = x[1][0] =
    x[1][2] = x[2][0] = x[2][1] = 0.0;
}

M33::M33(const double src[3][3])
{
    memcpy(x, src, 3 * 3 * sizeof(double));
}

M33::M33(double xx, double xy, double xz,
         double yx, double yy, double yz,
         double zx, double zy, double zz)
{
    x[0][0] = xx;
    x[0][1] = xy;
    x[0][2] = xz;
    x[1][0] = yx;
    x[1][1] = yy;
    x[1][2] = yz;
    x[2][0] = zx;
    x[2][1] = zy;
    x[2][2] = zz;
}

M33 &M33::operator= (const M33 &a)
{
    x[0][0] = a.x[0][0];
    x[0][1] = a.x[0][1];
    x[0][2] = a.x[0][2];
    x[1][0] = a.x[1][0];
    x[1][1] = a.x[1][1];
    x[1][2] = a.x[1][2];
    x[2][0] = a.x[2][0];
    x[2][1] = a.x[2][1];
    x[2][2] = a.x[2][2];
    return *this;
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

M33 &M33::operator*= (const double s)
{
    x[0][0] *= s;
    x[0][1] *= s;
    x[0][2] *= s;
    x[1][0] *= s;
    x[1][1] *= s;
    x[1][2] *= s;
    x[2][0] *= s;
    x[2][1] *= s;
    x[2][2] *= s;
    return *this;
}

M33 &M33::operator/= (const double s)
{
    assert(s != 0.0);

    x[0][0] /= s;
    x[0][1] /= s;
    x[0][2] /= s;
    x[1][0] /= s;
    x[1][1] /= s;
    x[1][2] /= s;
    x[2][0] /= s;
    x[2][1] /= s;
    x[2][2] /= s;
    return *this;
}

M33 &M33::invert()
{
    double det;
    M33 res;

    det = determinant();

    assert(det != 0.0);

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

M33 M33::getRotateXMatrix(const double angle)
{
    M33 A;

    double cosinus = cos(DegToRad(angle));
    double sinus = sin(DegToRad(angle));

    A.x[1][1] = cosinus;
    A.x[1][2] = sinus;
    A.x[2][1] = -sinus;
    A.x[2][2] = cosinus;

    return A;
}

M33 M33::getRotateYMatrix(const double angle)
{
    M33 A;

    double cosinus = cos(DegToRad(angle));
    double sinus = sin(DegToRad(angle));

    A.x[0][0] = cosinus;
    A.x[0][2] = -sinus;
    A.x[2][0] = sinus;
    A.x[2][2] = cosinus;

    return A;
}

M33 M33::getRotateZMatrix(const double angle)
{
    M33 A;

    double cosinus = cos(DegToRad(angle));
    double sinus = sin(DegToRad(angle));

    A.x[0][0] = cosinus;
    A.x[0][1] = sinus;
    A.x[1][0] = -sinus;
    A.x[1][1] = cosinus;

    return A;
}

M33 M33::getRotateYawPitchRollMatrix(const double yaw, const double pitch, const double roll)
{
    return getRotateYMatrix(yaw) * getRotateZMatrix(roll) * getRotateXMatrix(pitch);
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

M33 operator* (const M33 &a, const double s)
{
    M33 res = a;

    return res *= s;
}

M33 operator* (const double s, const M33 &b)
{
    M33 res = b;

    return res *= s;
}

vec3 operator* (const M33 &a, const vec3 &b)
{
    return vec3(a.x[0][0] * b.x + a.x[0][1] * b.y + a.x[0][2] * b.z,
                a.x[1][0] * b.x + a.x[1][1] * b.y + a.x[1][2] * b.z,
                a.x[2][0] * b.x + a.x[2][1] * b.y + a.x[2][2] * b.z);
}

}
