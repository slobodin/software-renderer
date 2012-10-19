/*
 * common_math.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef COMMON_MATH_H
#define COMMON_MATH_H

#include "comm_pch.h"

#include <cmath>
#include <climits>

namespace math
{

//! Some kind of machine epsilons.
const float EPSILON_E1 = 1E-1;
const float EPSILON_E3 = 1E-3;
const float EPSILON_E4 = 1E-4;
const float EPSILON_E5 = 1E-5;
const float EPSILON_E6 = 1E-6;
const float EPSILON_E12 = 1E-12;

//! Float point comparsion of two values.
/*!
  * \returns true if x == y with some imprecision.
  */
inline bool DCMP(float x, float y, float pres = EPSILON_E12)
{
    return (fabs(x - y) < pres);
}

//! Degrees to radians conversion function.
inline float DegToRad(float ang) { return ang * (M_PI / 180.0); }
//! Radians to degrees conversion function.
inline float RadToDeg(float rad) { return rad * (180.0 / M_PI); }

}

#endif // COMMON_MATH_H
