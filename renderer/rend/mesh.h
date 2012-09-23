/*
 * mesh.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef MESH_H
#define MESH_H

#include "comm_pch.h"

#include "vertexbuffer.h"
#include "m44.h"
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
    list<VertexBuffer> m_submeshes;

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

    void setShadingMode(Material::ShadeMode shMode);
    void setSideType(Material::SideType side);

    const list<VertexBuffer> &getSubmeshes() const { return m_submeshes; }
    list<VertexBuffer>       &getSubmeshes() { return m_submeshes; }

    sptr(Mesh) clone() const;

    Mesh(const Mesh &) = delete;
    Mesh &operator= (const Mesh &) = delete;
};

}

#endif // MESH_H
