/*
 * poly.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef POLY_H
#define POLY_H

#include "comm_pch.h"

#include "vertex.h"
#include "material.h"

namespace math
{

class Triangle
{
public:
    enum WindingOrder
    {
        WO_CW,
        WO_CCW
    };

    enum SideType
    {
        ST_1_SIDED,
        ST_2_SIDED
    };

private:
    vertex m_verts[3];
    vec3 m_normal;

    // FIXME: material id!
    rend::Material m_material;
    WindingOrder m_windingOrder;
    SideType m_sideType;

public:
    Triangle(WindingOrder wo = WO_CW, SideType st = ST_2_SIDED);
    Triangle(const vertex *arr, WindingOrder wo = WO_CW, SideType st = ST_2_SIDED);

    const vertex &v(const size_t ind) const;
    vertex &v(const size_t ind);

    const rend::Material &material() const { return m_material; }
    rend::Material &material() { return m_material; }

    void setWindingOrder(WindingOrder wo) { m_windingOrder = wo; }
    WindingOrder getWindingOrder() const { return m_windingOrder; }

    void setSideType(SideType st) { m_sideType = st; }
    SideType getSideType() const { return m_sideType; }

    void computeNormal();
    vec3 normal() const { return m_normal; }

    friend bool ZCompareAvg(const math::Triangle &t1, const math::Triangle &t2);
    friend bool ZCompareMin(const math::Triangle &t1, const math::Triangle &t2);
};

inline bool ZCompareAvg(const math::Triangle &t1, const math::Triangle &t2)
{
    double avgz = 0.33333 * (t1.m_verts[0].p.z + t1.m_verts[1].p.z + t1.m_verts[2].p.z);
    double avgotherz = 0.33333 * (t2.m_verts[0].p.z + t2.m_verts[1].p.z + t2.m_verts[2].p.z);

    if (avgz < avgotherz)
        return true;

    return false;
}

inline bool ZCompareMin(const Triangle &t1, const Triangle &t2)
{
//    std::min()
    return true;
}

}

#endif // POLY_H
