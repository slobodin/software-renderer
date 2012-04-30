/*
 * vector3.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef vector3_H
#define vector3_H

#include "comm_pch.h"

#include "common_math.h"

namespace math
{

//! Three-component row vector.
/*! v = (x, y, z) */
template<typename T>
struct vector3
{
    T x, y, z;
    vector3(T xx = 0.0, T yy = 0.0, T zz = 0.0) : x(xx), y(yy), z(zz) { }

    vector3 &operator+= (const vector3 &other);
    vector3 &operator-= (const vector3 &other);
    vector3 &operator*= (T s);
    vector3 &operator/= (T s);

    vector3 operator-() const;

    bool operator== (const vector3 &other) const;
    bool operator!= (const vector3 &other) const;

    operator const T* () const;

    T length() const;
    vector3 &normalize();
    void set(T xx, T yy, T zz);
    void set(const vector3 &other);
    void zero();
    bool isZero() const;
    T dotProduct(const vector3 &other) const;
    vector3 crossProduct(const vector3 &other) const;

    template<typename T1>
    friend vector3<T1> operator+ (const vector3<T1> &a, const vector3<T1> &b);
    template<typename T1>
    friend vector3<T1> operator- (const vector3<T1> &a, const vector3<T1> &b);
    template<typename T1>
    friend vector3<T1> operator* (const vector3<T1> &a, T1 b);
    template<typename T1>
    friend vector3<T1> operator* (T1 a, const vector3<T1> &b);
    template<typename T1>
    friend vector3<T1> operator/ (const vector3<T1> &a, T b);

    template<typename T1>
    friend std::ostream &operator<< (std::ostream &os, const vector3<T1> &v);

    template<typename T1>
    friend bool comparex(const vector3<T1> &a, const vector3<T1> &b);
    template<typename T1>
    friend bool comparey(const vector3<T1> &a, const vector3<T1> &b);
    template<typename T1>
    friend bool comparez(const vector3<T1> &a, const vector3<T1> &b);
};

template<typename T>
inline vector3<T> &vector3<T>::operator+= (const vector3<T> &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

template<typename T>
inline vector3<T> &vector3<T>::operator-= (const vector3<T> &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

template<typename T>
inline vector3<T> &vector3<T>::operator*= (T s)
{
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

template<typename T>
inline vector3<T> &vector3<T>::operator/= (T s)
{
    assert(s != 0.0);
    x /= s;
    y /= s;
    z /= s;
    return *this;
}

template<typename T>
inline vector3<T> vector3<T>::operator-() const
{
    return vector3<T>(-x, -y, -z);
}

template<typename T>
inline bool vector3<T>::operator== (const vector3<T> &other) const
{
    if (fabs(x - other.x) > EPSILON_E3)
        return false;
    if (fabs(y - other.y) > EPSILON_E3)
        return false;
    if (fabs(z - other.z) > EPSILON_E3)
        return false;
    return true;
}

template<typename T>
inline bool vector3<T>::operator!= (const vector3<T> &other) const
{
    if (fabs(x - other.x) > EPSILON_E3)
        return true;
    if (fabs(y - other.y) > EPSILON_E3)
        return true;
    if (fabs(z - other.z) > EPSILON_E3)
        return true;
    return false;
}

template<typename T>
inline vector3<T>::operator const T* () const
{
    return &x;
}

template<typename T>
inline T vector3<T>::length() const
{
    T t = x * x + y * y + z * z;
    assert(t != 0.0);
    return sqrt(t);
}

template<typename T>
inline vector3<T> &vector3<T>::normalize()
{
    if ((fabs(x - 0.0) < EPSILON_E6) &&
        (fabs(y - 0.0) < EPSILON_E6) &&
        (fabs(z - 0.0) < EPSILON_E6))
        return (*this);

    return (*this) /= length();
}

template<typename T>
inline void vector3<T>::set(T xx, T yy, T zz)
{
    x = xx;
    y = yy;
    z = zz;
}

template<typename T>
inline void vector3<T>::set(const vector3 &other)
{
    x = other.x;
    y = other.y;
    z = other.z;
}

template<typename T>
inline void vector3<T>::zero()
{
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

template<typename T>
inline bool vector3<T>::isZero() const
{
    return (x == 0.0) && (y == 0.0) && (z == 0.0);
}

template<typename T>
inline T vector3<T>::dotProduct(const vector3<T> &other) const
{
    return (x * other.x + y * other.y + z * other.z);
}

template<typename T>
inline vector3<T> vector3<T>::crossProduct(const vector3<T> &other) const
{
    return vector3<T>(y * other.z - z * other.y,
                      -(x * other.z - z * other.x),
                      x * other.y - y * other.x);
}

template<typename T1>
bool comparex(const vector3<T1> &a, const vector3<T1> &b)
{
    return a.x < b.x;
}

template<typename T1>
bool comparey(const vector3<T1> &a, const vector3<T1> &b)
{
    return a.y < b.y;
}

template<typename T1>
bool comparez(const vector3<T1> &a, const vector3<T1> &b)
{
    return a.z < b.z;
}

template<typename T1>
inline vector3<T1> operator+ (const vector3<T1> &a, const vector3<T1> &b)
{
    return vector3<T1>(a.x + b.x, a.y + b.y, a.z + b.z);
}

template<typename T1>
inline vector3<T1> operator- (const vector3<T1> &a, const vector3<T1> &b)
{
    return vector3<T1>(a.x - b.x, a.y - b.y, a.z - b.z);
}

template<typename T1>
inline vector3<T1> operator* (const vector3<T1> &a, T1 b)
{
    return vector3<T1>(a.x * b, a.y * b, a.z * b);
}

template<typename T1>
inline vector3<T1> operator* (T1 a, const vector3<T1> &b)
{
    return vector3<T1>(b.x * a, b.y * a, b.z * a);
}

template<typename T1>
inline vector3<T1> operator/ (const vector3<T1> &a, T1 b)
{
    assert(b != 0.0);
    return vector3<T1>(a.x / b, a.y / b, a.z / b);
}

template<typename T1>
inline std::ostream &operator<< (std::ostream &os, const vector3<T1> &v)
{
    os << "[x: " << v.x << " y: " << v.y << " z: " << v.z << "]";
    return os;
}

typedef vector3<double> vec3;
typedef vector3<uint32_t> ivec3;

}

#endif // vector3_H
