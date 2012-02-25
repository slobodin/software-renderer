#ifndef POLY_H
#define POLY_H

#include "comm_pch.h"

#include "vec3.h"

namespace math
{

class Triangle
{
    vec3 m_verts[3];
public:
    Triangle();
    Triangle(const vec3 *arr);

    const vec3 &v(const size_t ind) const;
    vec3 &v(const size_t ind);
};

}

#endif // POLY_H
