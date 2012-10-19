/*
 * m44.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "m44.h"

#include "common_math.h"
#include "m33.h"
#include "vec3.h"

namespace math
{

M44::M44()
{
    reset();
}

M44::M44(const float (&src)[4][4])
{
    set(src);
}

M44::M44(float a00, float a01, float a02, float a03,
         float a10, float a11, float a12, float a13,
         float a20, float a21, float a22, float a23,
         float a30, float a31, float a32, float a33)
{
    set(a00, a01, a02, a03,
        a10, a11, a12, a13,
        a20, a21, a22, a23,
        a30, a31, a32, a33);
}

M44::M44(const M33 &rotScale, const vec3 &translation)
{
    set(rotScale, translation);
}

M44::M44(const vec3 &translation)
{
    set(translation);
}

M44::M44(const M33 &rotScale)
{
    set(rotScale);
}

void M44::set(const float (&src)[4][4])
{
    memcpy(x, src, 4 * 4 * sizeof(float));
}

void M44::set(float a00, float a01, float a02, float a03,
              float a10, float a11, float a12, float a13,
              float a20, float a21, float a22, float a23,
              float a30, float a31, float a32, float a33)
{
    x[0][0] = a00;
    x[0][1] = a01;
    x[0][2] = a02;
    x[0][3] = a03;
    x[1][0] = a10;
    x[1][1] = a11;
    x[1][2] = a12;
    x[1][3] = a13;
    x[2][0] = a20;
    x[2][1] = a21;
    x[2][2] = a22;
    x[2][3] = a23;
    x[3][0] = a30;
    x[3][1] = a31;
    x[3][2] = a32;
    x[3][3] = a33;
}

void M44::set(const M33 &rotScale, const vec3 &translation)
{
    // first row
    x[0][0] = rotScale.x[0][0];
    x[0][1] = rotScale.x[0][1];
    x[0][2] = rotScale.x[0][2];
    x[0][3] = 0.0;
    // second row
    x[1][0] = rotScale.x[1][0];
    x[1][1] = rotScale.x[1][1];
    x[1][2] = rotScale.x[1][2];
    x[1][3] = 0.0;
    // third row
    x[2][0] = rotScale.x[2][0];
    x[2][1] = rotScale.x[2][1];
    x[2][2] = rotScale.x[2][2];
    x[2][3] = 0.0;
    // fourth row
    x[3][0] = translation.x;
    x[3][1] = translation.y;
    x[3][2] = translation.z;
    x[3][3] = 1.0;
}

void M44::set(const vec3 &translation)
{
    // first row
    x[0][0] = 1.0;
    x[0][1] = 0.0;
    x[0][2] = 0.0;
    x[0][3] = 0.0;
    // second row
    x[1][0] = 0.0;
    x[1][1] = 1.0;
    x[1][2] = 0.0;
    x[1][3] = 0.0;
    // third row
    x[2][0] = 0.0;
    x[2][1] = 0.0;
    x[2][2] = 1.0;
    x[2][3] = 0.0;
    // fourth row
    x[3][0] = translation.x;
    x[3][1] = translation.y;
    x[3][2] = translation.z;
    x[3][3] = 1.0;
}

void M44::set(const M33 &rotScale)
{
    // first row
    x[0][0] = rotScale.x[0][0];
    x[0][1] = rotScale.x[0][1];
    x[0][2] = rotScale.x[0][2];
    x[0][3] = 0.0;
    // second row
    x[1][0] = rotScale.x[1][0];
    x[1][1] = rotScale.x[1][1];
    x[1][2] = rotScale.x[1][2];
    x[1][3] = 0.0;
    // third row
    x[2][0] = rotScale.x[2][0];
    x[2][1] = rotScale.x[2][1];
    x[2][2] = rotScale.x[2][2];
    x[2][3] = 0.0;
    // fourth row
    x[3][0] = 0.0;
    x[3][1] = 0.0;
    x[3][2] = 0.0;
    x[3][3] = 1.0;
}

void M44::reset()
{
    memset(&x[0], 0, sizeof(float) * 4 * 4);
    x[0][0] = x[1][1] = x[2][2] = x[3][3] = 1.0;
}

M33 M44::getM() const
{
    return M33(x[0][0], x[0][1], x[0][2],
               x[1][0], x[1][1], x[1][2],
               x[2][0], x[2][1], x[2][2]);
}

vec3 M44::getV() const
{
    return vec3(x[3][0], x[3][1], x[3][2]);
}

M44 &M44::operator+= (const M44 &a)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            x[i][j] += a.x[i][j];

    return *this;
}

M44 &M44::operator-= (const M44 &a)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            x[i][j] -= a.x[i][j];

    return *this;
}

M44 &M44::operator*= (const M44 &a)
{
    M44 res = *this * a;

    return *this = res;
}

M44 &M44::operator*= (float s)
{
    BOOST_FOREACH (float (&row)[4], x)
        BOOST_FOREACH (float &el, row)
            el *= s;

    return *this;
}

M44 &M44::operator/= (float s)
{
    assert(!DCMP(s, 0.0));

    BOOST_FOREACH (float (&row)[4], x)
        BOOST_FOREACH (float &el, row)
            el /= s;

    return *this;
}

bool M44::operator== (const M44 &a) const
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (!DCMP(x[i][j], a.x[i][j]))
                return false;

    return true;
}

M44 &M44::transpose()
{
    M44 res;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            res.x[i][j] = x[j][i];

    return *this = res;
}

M44 operator+ (const M44 &a, const M44 &b)
{
    M44 res;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            res.x[i][j] = a.x[i][j] + b.x[i][j];

    return res;
}

M44 operator- (const M44 &a, const M44 &b)
{
    M44 res;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            res.x[i][j] = a.x[i][j] - b.x[i][j];

    return res;
}

M44 operator* (const M44 &a, const M44 &b)
{
    M44 res;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            res.x[i][j] = a.x[i][0] * b.x[0][j] +
                          a.x[i][1] * b.x[1][j] +
                          a.x[i][2] * b.x[2][j] +
                          a.x[i][3] * b.x[3][j];
        }
    }

    return res;
}

M44 operator* (const M44 &a, float s)
{
    M44 res = a;

    return res *= s;
}

M44 operator* (float s, const M44 &a)
{
    M44 res = a;

    return res *= s;
}

vec3 operator* (const vec3 &v, const M44 &a)
{
    float res[4];  // result 4-vector

    res[0] = v.x * a.x[0][0] + v.y * a.x[1][0] + v.z * a.x[2][0] + /*1.0 * */a.x[3][0];
    res[1] = v.x * a.x[0][1] + v.y * a.x[1][1] + v.z * a.x[2][1] + /*1.0 * */a.x[3][1];
    res[2] = v.x * a.x[0][2] + v.y * a.x[1][2] + v.z * a.x[2][2] + /*1.0 * */a.x[3][2];
    res[3] = v.x * a.x[0][3] + v.y * a.x[1][3] + v.z * a.x[2][3] + /*1.0 * */a.x[3][3];

    if (fabs(res[3] - 1.0) < 0.00000001/*std::numeric_limits<float>::epsilon()*/)   // equals to 1.0
    {
        return vec3(res[0], res[1], res[2]);
    }
    else
    {
        return vec3(res[0] / res[3], res[1] / res[3], res[2] / res[3]);
    }
}

}
