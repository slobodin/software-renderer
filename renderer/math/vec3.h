#ifndef VEC3_H
#define VEC3_H

#include "comm_pch.h"

#include "common_math.h"

namespace math
{

//! 3-vector
struct vec3
{
    double x, y, z;
    vec3(const double xx = 0.0, const double yy = 0.0, const double zz = 0.0) : x(xx), y(yy), z(zz) { }

    vec3 &operator+= (const vec3 &other);
    vec3 &operator-= (const vec3 &other);
    vec3 &operator*= (const double s);
    vec3 &operator/= (const double s);

    vec3 operator-() const;

    bool operator== (const vec3 &other) const;
    bool operator!= (const vec3 &other) const;

    operator const double* () const;

    double length() const;
    vec3 &normalize();
    void set(const double xx, const double yy, const double zz);
    void set(const vec3 &other);
    void zero();
    double dotProduct(const vec3 &other);
    vec3 crossProduct(const vec3 &other);

    friend vec3 operator+ (const vec3 &a, const vec3 &b);
    friend vec3 operator- (const vec3 &a, const vec3 &b);
    friend vec3 operator* (const vec3 &a, const double b);
    friend vec3 operator* (const double a, const vec3 &b);
    friend vec3 operator/ (const vec3 &a, const double b);

    friend std::ostream &operator<< (std::ostream &os, const vec3 &v);
};


inline vec3 &vec3::operator+= (const vec3 &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

inline vec3 &vec3::operator-= (const vec3 &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

inline vec3 &vec3::operator*= (const double s)
{
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

inline vec3 &vec3::operator/= (const double s)
{
    assert(s != 0.0);
    x /= s;
    y /= s;
    z /= s;
    return *this;
}

inline vec3 vec3::operator-() const
{
    return vec3(-x, -y, -z);
}

inline bool vec3::operator== (const vec3 &other) const
{
    if (fabs(x - other.x) > EPSILON_E3)
        return false;
    if (fabs(y - other.y) > EPSILON_E3)
        return false;
    if (fabs(z - other.z) > EPSILON_E3)
        return false;
    return true;
}

inline bool vec3::operator!= (const vec3 &other) const
{
    if (fabs(x - other.x) > EPSILON_E3)
        return true;
    if (fabs(y - other.y) > EPSILON_E3)
        return true;
    if (fabs(z - other.z) > EPSILON_E3)
        return true;
    return false;
}

inline vec3::operator const double* () const
{
    return &x;
}

inline double vec3::length() const
{
    double t = x * x + y * y + z * z;
    assert(t != 0.0);
    return sqrt(t);
}

inline vec3 &vec3::normalize()
{
    if ((fabs(x - 0.0) < EPSILON_E6) &&
        (fabs(y - 0.0) < EPSILON_E6) &&
        (fabs(z - 0.0) < EPSILON_E6))
        return (*this);

    double temp = length();
    assert(temp != 0.0);
    return (*this) /= length();
}

inline void vec3::set(const double xx, const double yy, const double zz)
{
    x = xx;
    y = yy;
    z = zz;
}

inline void vec3::set(const vec3 &other)
{
    x = other.x;
    y = other.y;
    z = other.z;
}

inline void vec3::zero()
{
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

inline double vec3::dotProduct(const vec3 &other)
{
    return (x * other.x + y * other.y + z * other.z);
}

inline vec3 vec3::crossProduct(const vec3 &other)
{
    return vec3(y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x);
}

inline vec3 operator+ (const vec3 &a, const vec3 &b)
{
    return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}
inline vec3 operator- (const vec3 &a, const vec3 &b)
{
    return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline vec3 operator* (const vec3 &a, const double b)
{
    return vec3(a.x * b, a.y * b, a.z * b);
}

inline vec3 operator* (const double a, const vec3 &b)
{
    return vec3(b.x * a, b.y * a, b.z * a);
}

inline vec3 operator/ (const vec3 &a, const double b)
{
    assert(b != 0.0);
    return vec3(a.x / b, a.y / b, a.z / b);
}

inline std::ostream &operator<< (std::ostream &os, const vec3 &v)
{
    os << "[x: " << v.x << " y: " << v.y << " z: " << v.z << "]";
    return os;
}

}

#endif // VEC3_H
