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
    //! x[row][col].
    float x[3][3];

    //! Default ctor.
    /*! Default identity matrix. */
    M33();
    //! Array ctor.
    M33(const float (&src)[3][3]);
    //! Component ctor.
    M33(float a00, float a01, float a02,
        float a10, float a11, float a12,
        float a20, float a21, float a22);

    //! Set elements with array.
    void set(const float (&src)[3][3]);
    //! Set elements.
    void set(float a00, float a01, float a02,
             float a10, float a11, float a12,
             float a20, float a21, float a22);
    //! Reset to identity matrix.
    void reset();

    //! Matrix addition.
    M33 &operator+= (const M33 &a);
    //! Matrix subtraction.
    M33 &operator-= (const M33 &a);
    //! Matrix multiplication.
    M33 &operator*= (const M33 &a);
    //! Scalar multiplication.
    M33 &operator*= (float s);
    //! 1/scalar multiplication.
    M33 &operator/= (float s);

    //! Equality check.
    bool operator== (const M33 &a) const;

    //! Matrix inversion.
    M33 &invert();
    //! Matrix transposition.
    M33 &transpose();
    //! Determinant computing.
    float determinant() const;

    //! Returns matrix memory address.
    float *getPointer() { return reinterpret_cast<float *>(x); }

    //! Makes scale matrix from given 3d vector.
    /*!
      * (sx 0 0)
      * (0 sy 0)
      * (0 0 sz)
      */
    static M33 getScaleMatrix(const vec3 &vect);

    //! Makes matrix represents rotation about the X-axis by an given angle.
    /*!
      * \param angle Rotation angle in degrees (enabled by default).
      * \param rads If true - angle in radians.
      * \returns X-rotation matrix.
      */
    static M33 getRotateXMatrix(float angle, bool rads = false);

    //! Makes matrix represents rotation about the Y-axis by an given angle.
    /*!
      * \param angle Rotation angle in degrees (enabled by default).
      * \param rads If true - angle in radians.
      * \returns Y-rotation matrix.
      */
    static M33 getRotateYMatrix(float angle, bool rads = false);

    //! Makes matrix represents rotation about the Z-axis by given angle.
    /*!
      * \param angle Rotation angle in degrees (enabled by default).
      * \param rads If true - angle in radians.
      * \returns Z-rotation matrix.
      */
    static M33 getRotateZMatrix(float angle, bool rads = false);

    //! Makes matrix represents three sequential rotations about Y -> Z -> X axis
    /*!
      \param yaw angle in degrees (by default). Rotation about the Y axis.
      \param pitch angle in degrees (by default). Rotation about the X axis.
      \param roll angle in degrees (by default). Rotation about the Z axis.
      \param rads radians or degrees.
      \returns Result rotation matrix.
      */
    static M33 getRotateYawPitchRollMatrix(float yaw,
                                           float pitch,
                                           float roll,
                                           bool rads = false);

    //! Addition of two matrices.
    friend M33 operator+ (const M33 &a, const M33 &b);
    //! Subtraction of two matrices.
    friend M33 operator- (const M33 &a, const M33 &b);
    //! Multiplication of two matrices.
    friend M33 operator* (const M33 &a, const M33 &b);
    //! Scalar multiplication.
    friend M33 operator* (const M33 &a, float s);
    //! Scalar multiplication.
    friend M33 operator* (float s, const M33 &a);

    //! 3-vector and 3x3 matrix multiplication.
    /*!
      *           |1 2 3|
      * (1 2 3) * |4 5 6|
      *           |7 8 9|
      */
    friend vec3 operator* (const vec3 &v, const M33 &a);
};

}

#endif // M22_H
