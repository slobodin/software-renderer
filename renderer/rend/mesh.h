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
#include "model.h"
#include "resource.h"

namespace rend
{

//! Vertex buffers containter.
/*!
  * Base renderable triangle mesh.
  */
class Mesh : public base::Resource, public Model
{
public:
    enum MeshType
    {
        MT_MESH_UNDEFINED,              /*!< Undefined mesh type, can't render. */
        MT_MESH_INDEXEDTRIANGLELIST,    /*!< Index triplet in each vertex buffer define the triangle. */
        MT_MESH_TRIANGLELIST,           /*!< Vertex triplets in each vertex buffer define the triangle. */
        MT_MESH_LINELIST                /*!< Each two vertices define the line. */
    };

private:

    //! Mesh consists of some submeshes, which holds vertex data and one material.
    list<VertexBuffer> m_submeshes;
    //! Type of the mesh.
    MeshType m_type;

public:
    //! Default ctor.
    Mesh(MeshType mt = MT_MESH_UNDEFINED);
    //! Dtor.
    ~Mesh();

    //! Appends submesh to this mesh.
    void appendSubmesh(const VertexBuffer &submesh);

    //! Returns mesh type.
    MeshType type() { return m_type; }
    //! Sets mesh type.
    void setType(MeshType mt) { m_type = mt; }

    //! Returns vertex count of all submeshes.
    int numVertices() const;
};

}

#endif // MESH_H
