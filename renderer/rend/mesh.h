#ifndef MESH_H
#define MESH_H

#include "comm_pch.h"

#include "affinetransform.h"
#include "resource.h"
#include "boundingsphere.h"

namespace rend
{

class Mesh : public base::Resource
{
public:
    enum MeshType
    {
        MT_MESH_UNDEFINED,
        // Primitive is vertex and index list. Index triplets define the triangles.
        MT_MESH_INDEXEDTRIANGLELIST,
        // Primitive is vertex list. Vertex triplets define the triangles.
        MT_MESH_TRIANGLELIST
    };

private:
    vector<math::vec3> m_vertices;
    vector<int> m_indices;
    MeshType m_type;

    math::AffineTransform m_worldTransformation;
    BoundingSphere m_boundingSphere;

public:
    Mesh(const vector<math::vec3> &vertices,
         const vector<int> &indices,
         const MeshType type);
    ~Mesh();

    size_t numVertices() const;
    const vector<math::vec3> &vertices() const;
    const vector<int> &indices() const;
    MeshType type() const;

    void setPosition(const math::vec3 &pos);
    void setRotation(const math::vec3 &angles);
    void setTransformation(const math::AffineTransform &tr);
};

}

#endif // MESH_H
