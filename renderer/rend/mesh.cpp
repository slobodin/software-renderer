#include "mesh.h"

namespace rend
{

Mesh::Mesh(const vector<math::vec3> &vertices,
           const vector<int> &indices,
           const MeshType type)
    : m_vertices(vertices),
      m_indices(indices),
      m_type(type)
{
}

Mesh::~Mesh()
{
}

size_t Mesh::numVertices() const
{
    return m_vertices.size();
}

const vector<math::vec3> &Mesh::vertices() const
{
    return m_vertices;
}

const vector<int> &Mesh::indices() const
{
    return m_indices;
}

Mesh::MeshType Mesh::type() const
{
    return m_type;
}

void Mesh::setPosition(const math::vec3 &pos)
{
}

void Mesh::setRotation(const math::vec3 &angles)
{
}

void Mesh::setTransformation(const math::AffineTransform &tr)
{
}

}
