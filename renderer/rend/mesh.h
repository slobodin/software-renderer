/*
 * mesh.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef MESH_H
#define MESH_H

#include "vertexbuffer.h"
#include "../math/m44.h"
#include "material.h"

namespace rend
{

//! Vertex buffers containter.
/*!
  * Base renderable triangle mesh.
  */
class Mesh
{
    //! Mesh consists of some submeshes, which holds vertex data and one material.
    std::list<VertexBuffer> m_submeshes;

    //! Bounding sphere.
    BoundingSphere m_boundingSphere;

public:
    //! Default ctor.
    Mesh();
    //! Dtor.
    ~Mesh();

    //! Appends submesh to this mesh.
    void appendSubmesh(const VertexBuffer &submesh);

    void computeBoundingSphere(const math::M44 &transform);
    const BoundingSphere &getBoundingSphere() const;

    //! Returns vertex count of all submeshes.
    int numVertices() const;
    int numSubMeshes() const;
    int numTriangles() const;

    void setShadingMode(Material::ShadeMode shMode);
    void setAlpha(int alpha);
    void setTexture(sptr(Texture) texture);
    void setSideType(Material::SideType side);

    const std::list<VertexBuffer> &getSubmeshes() const { return m_submeshes; }
    std::list<VertexBuffer>       &getSubmeshes() { return m_submeshes; }

    sptr(Mesh) clone() const;

    NONCOPYABLE(Mesh)
};

}

#endif // MESH_H
