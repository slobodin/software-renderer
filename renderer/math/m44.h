/*
 * m44.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef M44_H
#define M44_H

#include "comm_pch.h"

namespace math
{

struct M33;
struct vec3;

struct M44
{
    //! x[row][col].
    double x[4][4];

    //! Default ctor.
    /*! Default identity matrix. */
    M44();
    //! Array ctor.
    M44(const double (&src)[4][4]);
    //! Component ctor.
    M44(double a00, double a01, double a02, double a03,
        double a10, double a11, double a12, double a13,
        double a20, double a21, double a22, double a23,
        double a30, double a31, double a32, double a33);
    //! Affine transform ctor.
    M44(const M33 &rotScale, const vec3 &translation);

    //! Set elements with array.
    void set(const double (&src)[4][4]);
    //! Set elements.
    void set(double a00, double a01, double a02, double a03,
             double a10, double a11, double a12, double a13,
             double a20, double a21, double a22, double a23,
             double a30, double a31, double a32, double a33);
    //! Set affine transform.
    void set(const M33 &rotScale, const vec3 &translation);
    //! Reset to identity matrix.
    void reset();

    //! Matrix addition.
    M44 &operator+= (const M44 &a);
    //! Matrix subtraction.
    M44 &operator-= (const M44 &a);
    //! Matrix multiplication.
    M44 &operator*= (const M44 &a);
    //! Scalar multiplication.
    M44 &operator*= (double s);
    //! 1/scalar multiplication.
    M44 &operator/= (double s);

    //! Equality check.
    bool operator== (const M44 &a) const;

    //! Matrix transposition.
    M44 &transpose();

    //! Returns matrix memory address.
    double *getPointer() { return reinterpret_cast<double *>(x); }

    //! Addition of two matrices.
    friend M44 operator+ (const M44 &a, const M44 &b);
    //! Subtraction of two matrices.
    friend M44 operator- (const M44 &a, const M44 &b);
    //! Multiplication of two matrices.
    friend M44 operator* (const M44 &a, const M44 &b);
    //! Scalar multiplication.
    friend M44 operator* (const M44 &a, double s);
    //! Scalar multiplication.
    friend M44 operator* (double s, const M44 &a);

    //! 3-vector (fake vector with 4th "w" component = 1) and 4x4 matrix multiplication.
    /*!
      *               |a00 a01 a02 a03|
      * (x y z 1.0) * |a10 a11 a12 a13|
      *               |a20 a21 a22 a23|
      *               |a30 a31 a32 a33|
      *
      * \returns vec3, which components divided by result 4-vector fourth component.
      */
    friend vec3 operator* (const vec3 &v, const M44 &a);
};

}

#endif // M44_H
