/*
 * vertexbuffer.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "comm_pch.h"

#include "vertex.h"
#include "boundingsphere.h"

namespace rend
{

class Material;
class Mesh;

//! Container for vertices and indices with same material.
/*!
  * Submesh.
  */
class VertexBuffer
{
    friend class Mesh; // because mesh is vertex buffer container.

    //! Some anti-boilerplate typedefs.
    typedef vector<math::vertex> VertexArray;
    typedef vector<uint16_t> IndexArray;

    //! Material of this vertices;
    sptr(Material) m_material;
    //! Vertices of the submesh.
    VertexArray m_vertices;
    //! Indices for the vertices.
    IndexArray m_indices;

    BoundingSphere m_boundingSphere;

    void computeBoundingSphere();
    void computeVertexNormals();

public:
    //! Default ctor.
    VertexBuffer();
    //! Dtor.
    ~VertexBuffer();

    //! Sets the material to this submesh.
    void setMaterial(sptr(Material) material);
    //! Appends vertices to this submesh.
    void appendVertices(const vector<math::vertex> &vertices, const vector<int> &indices);

    //! How many vertices in the buffer?
    int numVertices() const { return m_vertices.size(); }
    //! How many indices in the buffer?
    int numIndices() const { return m_indices.size(); }

    //! Gets i-th vertex from the array.
    math::vertex vertex(unsigned i) const { return m_vertices[i]; }
    //! Gets i-th index from the array.
    int index(unsigned i) const { return m_indices[i]; }

    //! Returns reference to all vertices of the submesh.
    const VertexArray &getVertices() const { return m_vertices; }
    //! Returns reference to all indices of the submesh.
    const IndexArray &getIndices() const { return m_indices; }
};

}

#endif // VERTEXBUFFER_H
