/*
 * vec2.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef VEC2_H
#define VEC2_H

#include "comm_pch.h"

#include "common_math.h"
#include "vec3.h"

namespace math
{

//! 2-vector
struct vec2
{
    double x, y;
    vec2(double xx = 0.0, double yy = 0.0) : x(xx), y(yy) { }

    vec2 &operator+= (const vec2 &other);
    vec2 &operator-= (const vec2 &other);
    vec2 &operator*= (const double s);
    vec2 &operator/= (const double s);

    vec2 operator-() const;

    bool operator== (const vec2 &other) const;
    bool operator!= (const vec2 &other) const;
    vec2 &operator= (const vec3 &v3);

    operator const double* () const;

    double length() const;
    vec2 &normalize();
    void set(const double xx, const double yy);
    void set(const vec2 &other);
    void zero();
    double dotProduct(const vec2 &other) const;

    friend vec2 operator+ (const vec2 &a, const vec2 &b);
    friend vec2 operator- (const vec2 &a, const vec2 &b);
    friend vec2 operator* (const vec2 &a, const double b);
    friend vec2 operator* (const double a, const vec2 &b);
    friend vec2 operator/ (const vec2 &a, const double b);

    friend std::ostream &operator<< (std::ostream &os, const vec2 &v);
};

inline vec2 &vec2::operator+= (const vec2 &other)
{
    x += other.x;
    y += other.y;
    return *this;
}

inline vec2 &vec2::operator-= (const vec2 &other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

inline vec2 &vec2::operator*= (const double s)
{
    x *= s;
    y *= s;
    return *this;
}

inline vec2 &vec2::operator/= (const double s)
{
    assert(s != 0.0);
    x /= s;
    y /= s;
    return *this;
}

inline vec2 vec2::operator-() const
{
    return vec2(-x, -y);
}

inline bool vec2::operator== (const vec2 &other) const
{
    if (fabs(x - other.x) > EPSILON_E3)
        return false;
    if (fabs(y - other.y) > EPSILON_E3)
        return false;
    return true;
}

inline bool vec2::operator!= (const vec2 &other) const
{
    if (fabs(x - other.x) > EPSILON_E3)
        return true;
    if (fabs(y - other.y) > EPSILON_E3)
        return true;
    return false;
}

inline vec2 &vec2::operator= (const vec3 &v3)
{
    x = v3.x;
    y = v3.y;

    return *this;
}

inline vec2::operator const double* () const
{
    return &x;
}

inline double vec2::length() const
{
    double t = x * x + y * y;
    assert(t != 0.0);
    return sqrt(t);
}

inline vec2 &vec2::normalize()
{
    if ((fabs(x - 0.0) < EPSILON_E6) &&
        (fabs(y - 0.0) < EPSILON_E6))
        return (*this);

    double temp = length();
    assert(temp != 0);
    return (*this) /= length();
}

inline void vec2::set(const double xx, const double yy)
{
    x = xx;
    y = yy;
}

inline void vec2::set(const vec2 &other)
{
    x = other.x;
    y = other.y;
}

inline void vec2::zero()
{
    x = 0.0;
    y = 0.0;
}

inline double vec2::dotProduct(const vec2 &other) const
{
    return x * other.x + y * other.y;
}

inline vec2 operator+ (const vec2 &a, const vec2 &b)
{
    return vec2(a.x + b.x, a.y + b.y);
}

inline vec2 operator- (const vec2 &a, const vec2 &b)
{
    return vec2(a.x - b.x, a.y - b.y);
}

inline vec2 operator* (const vec2 &a, const double b)
{
    return vec2(a.x * b, a.y * b);
}

inline vec2 operator* (const double a, const vec2 &b)
{
    return vec2(b.x * a, b.y * a);
}

inline vec2 operator/ (const vec2 &a, const double b)
{
    assert(b != 0.0);
    return vec2(a.x / b, a.y / b);
}

inline std::ostream &operator<< (std::ostream &os, const vec2 &v)
{
    os << "[x: " << v.x << " y: " << v.y << "]";
    return os;
}

}

#endif // VEC2_H
