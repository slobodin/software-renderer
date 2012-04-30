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
const double EPSILON_E1 = 1E-1;
const double EPSILON_E3 = 1E-3;
const double EPSILON_E4 = 1E-4;
const double EPSILON_E5 = 1E-5;
const double EPSILON_E6 = 1E-6;

//! Float point comparsion of two values.
/*!
  \returns true if x == y with some imprecision.
  */
inline bool DCMP(double x, double y, double pres = EPSILON_E6)
{
    return (fabs(x - y) < pres);
}

//! Degrees to radians conversion function.
inline double DegToRad(const double ang) { return ang * (M_PI / 180.0); }
//! Radians to degrees conversion function.
inline double RadToDeg(const double rad) { return rad * (180.0 / M_PI); }

}

#endif // COMMON_MATH_H
