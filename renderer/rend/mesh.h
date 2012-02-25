#ifndef MESH_H
#define MESH_H

#include "comm_pch.h"

#include "affinetransform.h"
#include "resource.h"
#include "boundingsphere.h"
#include "color.h"

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
        MT_MESH_TRIANGLELIST,
        // Two vertexs describes the line.
        MT_MESH_LINELIST
    };

private:
    vector<math::vec3> m_vertices;
    vector<size_t> m_indices;
    vector<Color3> m_colors;
    MeshType m_type;

    // TODO: make it in material-class
    bool m_wireframe;

    math::AffineTransform m_worldTransformation;
    BoundingSphere m_boundingSphere;

public:
    Mesh(const vector<math::vec3> &vertices,
         const vector<size_t> &indices,
         const MeshType type);
    ~Mesh();

    size_t numVertices() const;
    const vector<math::vec3> &vertices() const;
    const vector<size_t> &indices() const;
    MeshType type() const;

    bool &wireframe() { return m_wireframe; }

    void setPosition(const math::vec3 &pos);
    void setRotation(const math::vec3 &angles);
    void setTransformation(const math::AffineTransform &tr);
};

}

#endif // MESH_H
