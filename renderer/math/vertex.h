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

//! Vertex of the mesh.
/*!
  * Includes vertex point itself, point "normal",
  * texture coordinates and color.
  */
struct vertex
{
    //! Vertex point.
    vec3 p;
    //! Vertex normal.
    vec3 n;
    //! Vertex texture coordinates.
    vec2 t;
    //! Vertex color.
    rend::Color4 color;
    // TODO: maybe diffuse color and specular color?

    //! Default ctor.
    vertex();
};

}

#endif // VERTEX_H
