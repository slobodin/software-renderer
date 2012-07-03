/*
 * renderlist.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef RENDERLIST_H
#define RENDERLIST_H

#include "comm_pch.h"

#include "poly.h"

namespace math
{
struct M44;
}

namespace rend
{

class VertexBuffer;
class SceneObject;
class Camera;

class RenderList
{
    list<math::Triangle> m_triangles;

    static void createTriangles(const VertexBuffer &vertexBuffer,
                                const math::M44 &transform,
                                list<math::Triangle> &output);

public:
    //! Default ctor.
    RenderList() { }
    //! Dtor.
    ~RenderList() { }

    void append(const SceneObject &mesh);

    const list<math::Triangle> &triangles() const { return m_triangles; }
    list<math::Triangle>       &triangles() { return m_triangles; }

    void zsort();
    void removeBackfaces(const sptr(Camera) cam);
};

}

#endif // RENDERLIST_H
