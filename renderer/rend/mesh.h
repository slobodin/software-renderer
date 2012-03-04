#ifndef MESH_H
#define MESH_H

#include "comm_pch.h"

#include "affinetransform.h"
#include "resource.h"
#include "boundingsphere.h"
#include "color.h"
#include "material.h"

namespace rend
{

class Mesh : public base::Resource
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
    vector<math::vec3> m_vertices;
    vector<size_t> m_indices;
    vector<Material> m_materials;
    MeshType m_type;

    math::AffineTransform m_worldTransformation;
    BoundingSphere m_boundingSphere;

public:
    Mesh(const vector<math::vec3> &vertices,
         const vector<size_t> &indices,
         const vector<Material> &materials,
         const MeshType type);
    Mesh(const vector<math::vec3> &vertices,
         const MeshType type);
    ~Mesh();

    size_t numVertices() const;
    size_t numIndices() const;
    const vector<math::vec3> &vertices() const;
    const vector<size_t> &indices() const;
    const vector<Material> &materials() const;

    MeshType type() const;
    math::vec3 position() const { return m_worldTransformation.getv(); }
    const BoundingSphere &bsphere() const { return m_boundingSphere; }

    void setPosition(const math::vec3 &pos);
    void setRotation(const math::vec3 &angles);
    void setTransformation(const math::AffineTransform &tr);
};

}

#endif // MESH_H
