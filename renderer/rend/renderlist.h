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

class RenderList : boost::noncopyable
{
public:
    typedef vector<math::Triangle> Triangles;

private:
    Triangles m_triangles;
    int m_lastTriangleIndex;

    void createTriangles(const VertexBuffer &vertexBuffer,
                         const math::M44 &transform);

public:
    //! Default ctor.
    RenderList() { m_lastTriangleIndex = 0; }
    //! Dtor.
    ~RenderList() { }

    void prepare(int trianglesCount);
    void append(const sptr(SceneObject) obj);

    const Triangles &triangles() const { return m_triangles; }
    Triangles       &triangles() { return m_triangles; }

    void zsort();
    void removeBackfaces(const sptr(Camera) cam);

    size_t getSize() const { return m_triangles.size(); }
    size_t getCountOfNotClippedTriangles() const;
    bool empty() const { return m_triangles.empty(); }
};

}

#endif // RENDERLIST_H
