/*
 * mesh.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "mesh.h"

#include "m33.h"
#include "renderlist.h"

namespace rend
{

void Mesh::computeBoundingSphere()
{
    vector<math::vec3> points;
    for (size_t i = 0; i < m_vertices.size(); i++)
        points.push_back(m_vertices[i].p);

    m_boundingSphere.calculate(points);
}

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
    computeBoundingSphere();
}

Mesh::Mesh(const vector<math::vertex> &vertices,
           const MeshType type)
    : m_vertices(vertices),
      m_type(type),
      m_windingOrder(math::Triangle::WO_CW)
{
    computeBoundingSphere();
}

Mesh::~Mesh()
{
}

void Mesh::computeVertexNormals()
{
    vector<int> polysTouchVertex(m_vertices.size());

    switch(m_type)
    {
    case Mesh::MT_MESH_INDEXEDTRIANGLELIST:

        for(size_t ind = 0, t = 0; ind < m_indices.size(); ind += 3, t++)
        {
            size_t vindex0 = m_indices[ind];
            size_t vindex1 = m_indices[ind + 1];
            size_t vindex2 = m_indices[ind + 2];

            polysTouchVertex[vindex0]++;
            polysTouchVertex[vindex1]++;
            polysTouchVertex[vindex2]++;

            math::vec3 u = m_vertices[vindex1].p - m_vertices[vindex0].p;
            math::vec3 v = m_vertices[vindex2].p - m_vertices[vindex0].p;

            math::vec3 normal = u.crossProduct(v);

            m_vertices[vindex0].n += normal;
            m_vertices[vindex1].n += normal;
            m_vertices[vindex2].n += normal;
        }

        for (size_t vertex = 0; vertex < m_vertices.size(); vertex++)
        {
            if (polysTouchVertex[vertex] >= 1)
            {
                m_vertices[vertex].n /= polysTouchVertex[vertex];
                m_vertices[vertex].n.normalize();
            }
        }
        break;

    case Mesh::MT_MESH_TRIANGLELIST:

        *syslog << "Unsupported" << logerr;

        for(size_t v = 0; v < m_vertices.size(); v += 3)
        {
            if ((v + 2) >= m_vertices.size())
                break;

        }
        break;

    case Mesh::MT_MESH_UNDEFINED:
    default:
        *syslog << "Undefined mesh type" << logwarn;
        break;
    }
}

}
