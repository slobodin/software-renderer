/*
 * renderlist.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef RENDERLIST_H
#define RENDERLIST_H

#include "comm_pch.h"

#include "mesh.h"
#include "poly.h"

namespace rend
{

class Camera;

class RenderList
{
    list<math::Triangle> m_triangles;

public:
    RenderList();

    void append(const Mesh &mesh);

    const list<math::Triangle> &triangles() const { return m_triangles; }
    list<math::Triangle> &triangles() { return m_triangles; }

    void zsort();
    void removeBackfaces(const sptr(Camera) cam);
};

}

#endif // RENDERLIST_H
