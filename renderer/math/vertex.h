/*
 * vertex.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef VERTEX_H
#define VERTEX_H

#include "vec2.h"
#include "vec3.h"
#include "color.h"

namespace math
{

struct vertex
{
    math::vec3 p;   // vertex point
    math::vec3 n;   // vertex normal
    math::vec2 t;   // texture coords
    rend::Color3 color;

    vertex();
};

}

#endif // VERTEX_H
