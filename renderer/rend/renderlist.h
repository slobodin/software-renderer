#ifndef RENDERLIST_H
#define RENDERLIST_H

#include "mesh.h"
#include "poly.h"

namespace rend
{

class RenderList
{
    list<math::Triangle> m_triangles;

public:
    RenderList();

    void append(const Mesh &mesh);

    const list<math::Triangle> &triangles() const { return m_triangles; }
    list<math::Triangle> &triangles() { return m_triangles; }
};

}

#endif // RENDERLIST_H
