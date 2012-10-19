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

//! Two-component row vector.
/*!
  * v = (x, y)
  */
struct vec2
{
    //! X and Y coordinates
    float x, y;

    //! Default ctor.
    /*! Default zero vector. */
    vec2(float _x = 0.0f, float _y = 0.0f)
        : x(_x), y(_y) { }

    //! Addition assignment.
    vec2 &operator+= (const vec2 &other);
    //! Subtraction assignment.
    vec2 &operator-= (const vec2 &other);
    //! Scalar multiplication assignment.
    vec2 &operator*= (float s);
    //! 1/scalar multiplication.
    vec2 &operator/= (float s);

    //! Returns flipped vector.
    vec2 operator-() const;

    //! Equality check.
    bool operator== (const vec2 &other) const;
    //! Non-equality check.
    bool operator!= (const vec2 &other) const;
    //! Assignment with 3-vector.
    vec2 &operator= (const vec3 &v3);

    //! Convertion to pointer to float. Returns address of `this'.
    operator const float* () const;

    //! Vector's magnitude.
    float length() const;
    //! Normalizes this vector and returns it.
    vec2 &normalize();
    //! Some type of ctor.
    void set(float x, float y);
    //! Constructor from another vector.
    void set(const vec2 &other);
    //! Resets vector.
    void zero();
    //! Scalar product.
    float dotProduct(const vec2 &other) const;

    //! Addition of two vectors.
    friend vec2 operator+ (const vec2 &a, const vec2 &b);
    //! Subtraction of two vectors.
    friend vec2 operator- (const vec2 &a, const vec2 &b);
    //! Multiplication of vector and scalar.
    friend vec2 operator* (const vec2 &a, float b);
    //! Multiplication of vector and scalar.
    friend vec2 operator* (float a, const vec2 &b);
    //! Vector and 1/scalar multiplication.
    friend vec2 operator/ (const vec2 &a, float b);

    //! Logger helper. Writes `[x = , y = ]' in the stream
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

inline vec2 &vec2::operator*= (float s)
{
    x *= s;
    y *= s;

    return *this;
}

inline vec2 &vec2::operator/= (float s)
{
    assert(!DCMP(s, 0.0f));

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

inline vec2::operator const float* () const
{
    return &x;
}

inline float vec2::length() const
{
    float t = x * x + y * y;

    assert(!DCMP(t, 0.0f));

    return sqrt(t);
}

inline vec2 &vec2::normalize()
{
    if ((fabs(x - 0.0f) < EPSILON_E6) &&
        (fabs(y - 0.0f) < EPSILON_E6))
        return (*this);

    float temp = length();
    assert(!DCMP(temp, 0.0f));

    return (*this) /= length();
}

inline void vec2::set(float x, float y)
{
    this->x = x;
    this->y = y;
}

inline void vec2::set(const vec2 &other)
{
    x = other.x;
    y = other.y;
}

inline void vec2::zero()
{
    x = 0.0f;
    y = 0.0f;
}

inline float vec2::dotProduct(const vec2 &other) const
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

inline vec2 operator* (const vec2 &a, float b)
{
    return vec2(a.x * b, a.y * b);
}

inline vec2 operator* (float a, const vec2 &b)
{
    return vec2(b.x * a, b.y * a);
}

inline vec2 operator/ (const vec2 &a, float b)
{
    assert(!DCMP(b, 0.0f));
    return vec2(a.x / b, a.y / b);
}

inline std::ostream &operator<< (std::ostream &os, const vec2 &v)
{
    os << "[x: " << v.x << " y: " << v.y << "]";
    return os;
}

inline vec2 lerp(const vec2 &a, const vec2 &b, float t)
{
    return a + t * (b - a);
}

}

#endif // VEC2_H
