/*
 * m44.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef M44_H
#define M44_H

namespace math
{

struct M33;
struct vec3;

//! Row-column 4x4 Matrix.
/*!
  * (a00, a01, a02, a03)
  * (a10, a11, a12, a13)
  * (a20, a21, a22, a23)
  * (a30, a31, a32, a33)
  */
struct M44
{
    //! x[row][col].
    float x[4][4];

    //! Default ctor.
    /*! Default identity matrix. */
    M44();
    //! Array ctor.
    M44(const float (&src)[4][4]);
    //! Component ctor.
    M44(float a00, float a01, float a02, float a03,
        float a10, float a11, float a12, float a13,
        float a20, float a21, float a22, float a23,
        float a30, float a31, float a32, float a33);
    //! Affine transform ctor.
    M44(const M33 &rotScale, const vec3 &translation);
    //! Set affine transform.
    M44(const vec3 &translation);
    //! Set affine transform.
    M44(const M33 &rotScale);

    //! Set elements with array.
    void set(const float (&src)[4][4]);
    //! Set elements.
    void set(float a00, float a01, float a02, float a03,
             float a10, float a11, float a12, float a13,
             float a20, float a21, float a22, float a23,
             float a30, float a31, float a32, float a33);
    //! Set affine transform.
    void set(const M33 &rotScale, const vec3 &translation);
    //! Set affine transform.
    void set(const vec3 &translation);
    //! Set affine transform.
    void set(const M33 &rotScale);
    //! Reset to identity matrix.
    void reset();

    M33 getM() const;
    vec3 getV() const;

    //! Matrix addition.
    M44 &operator+= (const M44 &a);
    //! Matrix subtraction.
    M44 &operator-= (const M44 &a);
    //! Matrix multiplication.
    M44 &operator*= (const M44 &a);
    //! Scalar multiplication.
    M44 &operator*= (float s);
    //! 1/scalar multiplication.
    M44 &operator/= (float s);

    //! Equality check.
    bool operator== (const M44 &a) const;

    //! Matrix transposition.
    M44 &transpose();

    //! Returns matrix memory address.
    float *getPointer() { return reinterpret_cast<float *>(x); }

    //! Addition of two matrices.
    friend M44 operator+ (const M44 &a, const M44 &b);
    //! Subtraction of two matrices.
    friend M44 operator- (const M44 &a, const M44 &b);
    //! Multiplication of two matrices.
    friend M44 operator* (const M44 &a, const M44 &b);
    //! Scalar multiplication.
    friend M44 operator* (const M44 &a, float s);
    //! Scalar multiplication.
    friend M44 operator* (float s, const M44 &a);

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
