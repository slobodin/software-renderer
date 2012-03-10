/*
 * mesh.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef MESH_H
#define MESH_H

#include "comm_pch.h"

#include "resource.h"
#include "boundingsphere.h"
#include "color.h"
#include "material.h"
#include "model.h"
#include "poly.h"
#include "vertex.h"

namespace rend
{

class Mesh : public base::Resource, public Model
{
public:
    enum MeshType
    {
        MT_MESH_UNDEFINED,
        // Mesh is vertex and index list. Index triplets define the triangles.
        MT_MESH_INDEXEDTRIANGLELIST,
        // Mesh is vertex list. Vertex triplets define the triangles.
        MT_MESH_TRIANGLELIST
    };

private:
    vector<math::vertex> m_vertices;
    vector<size_t> m_indices;
    vector<Material> m_materials;   // FIXME
    MeshType m_type;

    BoundingSphere m_boundingSphere;
    math::Triangle::WindingOrder m_windingOrder;

public:
    Mesh(const vector<math::vertex> &vertices,
         const vector<size_t> &indices,
         const vector<Material> &materials,
         const MeshType type);

    Mesh(const vector<math::vertex> &vertices,
         const MeshType type);

    ~Mesh();

    size_t numVertices() const { return m_vertices.size(); }
    size_t numIndices() const { return m_indices.size(); }

    const vector<math::vertex> &vertices() const { return m_vertices; }
    const vector<size_t> &indices() const { return m_indices; }
    const vector<Material> &materials() const { return m_materials; }

    MeshType type() const { return m_type; }
    const BoundingSphere &bsphere() const { return m_boundingSphere; }

    void setWindingOrder(math::Triangle::WindingOrder wo) { m_windingOrder = wo; }
    math::Triangle::WindingOrder getWindingOrder() const { return m_windingOrder; }
};

}

#endif // MESH_H
