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

    const list<VertexBuffer> &getSubmeshes() const { return m_submeshes; }

    sptr(Mesh) clone() const;

private:
    Mesh(const Mesh &);
    Mesh &operator= (const Mesh &);
};

}

#endif // MESH_H
