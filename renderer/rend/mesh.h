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
#include "resource.h"

namespace rend
{

//! Vertex buffers containter.
/*!
  * Base renderable triangle mesh.
  */
class Mesh : public base::Resource
{
    //! Mesh consists of some submeshes, which holds vertex data and one material.
    list<VertexBuffer> m_submeshes;

public:
    //! Default ctor.
    Mesh();
    //! Dtor.
    ~Mesh();

    //! Appends submesh to this mesh.
    void appendSubmesh(const VertexBuffer &submesh);

    //! Returns vertex count of all submeshes.
    int numVertices() const;
    int numSubMeshes() const;

    const list<VertexBuffer> &getSubmeshes() const { return m_submeshes; }
};

}

#endif // MESH_H
