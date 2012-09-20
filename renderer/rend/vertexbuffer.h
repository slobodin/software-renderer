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
public:
    //! Some anti-boilerplate typedefs.
    typedef vector<math::vertex> VertexArray;
    typedef vector<uint16_t> IndexArray;

    enum VertexBufferType
    {
        UNDEFINED,
        INDEXEDTRIANGLELIST,    /*!< Index triplet in vertex buffer define the triangle. */
        TRIANGLELIST,           /*!< Vertex triplets in vertex buffer define the triangle. */
        LINELIST                /*!< Each two vertices define the line. */
    };

private:
    friend class Mesh; // because mesh is vertex buffer container.

    //! Type of vertices.
    VertexBufferType m_type;
    //! Material of this vertices;
    sptr(Material) m_material;
    //! Vertices of the submesh.
    VertexArray m_vertices;
    //! Indices for the vertices.
    IndexArray m_indices;

    //! Bounding sphere.
    BoundingSphere m_boundingSphere;

    //! Helper to compute bounding sphere.
    void computeBoundingSphere();
    //! Helper to compute vertex normals.
    void computeVertexNormals();

public:
    //! Default ctor.
    VertexBuffer(VertexBufferType type = UNDEFINED);
    //! Dtor.
    ~VertexBuffer();

    //! Sets the material to this submesh.
    void            setMaterial(sptr(Material) material);
    //! Gets material.
    sptr(Material)  getMaterial() const { return m_material; }

    //! Sets the type.
    void                setType(VertexBufferType type) { m_type = type; }
    //! Gets the type.
    VertexBufferType    getType() const { return m_type; }

    //! Appends vertices to this submesh.
    void appendVertices(const vector<math::vertex> &vertices, const vector<int> &indices);
    void appendVertices(const vector<math::vertex> &vertices);

    //! How many vertices in the buffer?
    int numVertices() const { return m_vertices.size(); }
    //! How many indices in the buffer?
    int numIndices() const { return m_indices.size(); }

    //! Gets i-th vertex from the array.
    math::vertex    vertex(unsigned i) const { return m_vertices[i]; }
    //! Gets i-th index from the array.
    int             index(unsigned i) const { return m_indices[i]; }

    //! Returns reference to all vertices of the submesh.
    const VertexArray&  getVertices() const { return m_vertices; }
    //! Returns reference to all indices of the submesh.
    const IndexArray&   getIndices() const { return m_indices; }
};

}

#endif // VERTEXBUFFER_H
