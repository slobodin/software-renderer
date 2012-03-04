#ifndef POLY_H
#define POLY_H

#include "comm_pch.h"

#include "vec3.h"
#include "material.h"

namespace math
{

class Triangle
{
    vec3 m_verts[3];
    rend::Material m_material;

public:
    Triangle();
    Triangle(const vec3 *arr);

    const vec3 &v(const size_t ind) const;
    vec3 &v(const size_t ind);

    void setMaterial(const rend::Material &material);
    const rend::Material &material() const { return m_material; }
    rend::Material &material() { return m_material; }

    friend bool ZCompareAvg(const math::Triangle &t1, const math::Triangle &t2);
};

inline bool ZCompareAvg(const math::Triangle &t1, const math::Triangle &t2)
{
    double avgz = 0.33333 * (t1.m_verts[0].z + t1.m_verts[1].z + t1.m_verts[2].z);
    double avgotherz = 0.33333 * (t2.m_verts[0].z + t2.m_verts[1].z + t2.m_verts[2].z);

    if (avgz < avgotherz)
        return true;

    return false;
}


}

#endif // POLY_H
