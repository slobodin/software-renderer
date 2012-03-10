/*
 * mesh.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "mesh.h"

#include "m33.h"

namespace rend
{

Mesh::Mesh(const vector<math::vertex> &vertices,
           const vector<size_t> &indices,
           const vector<Material> &materials,
           const MeshType type)
    : m_vertices(vertices),
      m_indices(indices),
      m_materials(materials),
      m_type(type),
      m_windingOrder(math::Triangle::WO_CW)
{
    vector<math::vec3> points;
    for (size_t i = 0; i < vertices.size(); i++)
        points.push_back(vertices[i].p);

    m_boundingSphere.calculate(points);
}

Mesh::Mesh(const vector<math::vertex> &vertices,
           const MeshType type)
    : m_vertices(vertices),
      m_type(type),
      m_windingOrder(math::Triangle::WO_CW)
{
    vector<math::vec3> points;
    for (size_t i = 0; i < vertices.size(); i++)
        points.push_back(vertices[i].p);

    m_boundingSphere.calculate(points);
}

Mesh::~Mesh()
{
}

}
