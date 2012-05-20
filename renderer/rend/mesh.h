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

    list<VertexBuffer> m_submeshes;
    MeshType m_type;

public:
    Mesh();
    ~Mesh();

    void appendSubmesh(const VertexBuffer &submesh);

    MeshType type() { return m_type; }
    void setType(MeshType mt) { m_type = mt; }
};

}

#endif // MESH_H
