/*
 * boundingsphere.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef BOUNDINGSPHERE_H
#define BOUNDINGSPHERE_H

#include "comm_pch.h"

#include "vec3.h"

namespace rend
{

class BoundingSphere
{
    math::vec3 m_centerPoint;
    double m_radius;

public:
    BoundingSphere();
    BoundingSphere(const vector<math::vec3> &vertices);
    ~BoundingSphere();

    math::vec3  center() const { return m_centerPoint; }
    double      radius() const { return m_radius; }

    void        calculate(const vector<math::vec3> &vertices);

    bool valid() const { return m_radius > 0.; }
};

}

#endif // BOUNDINGSPHERE_H
