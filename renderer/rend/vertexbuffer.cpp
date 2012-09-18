/*
 * vertexbuffer.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "vertexbuffer.h"

#include "material.h"
#include "mesh.h"

namespace rend
{

VertexBuffer::VertexBuffer(VertexBufferType type)
    : m_type(type)
{
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::setMaterial(boost::shared_ptr<Material> material)
{
    if (!material)
        return;

    m_material = material;
}

void VertexBuffer::appendVertices(const vector<math::vertex> &vertices, const vector<int> &indices)
{
    std::copy(vertices.begin(), vertices.end(), std::back_inserter(m_vertices));
    std::copy(indices.begin(), indices.end(), std::back_inserter(m_indices));

    computeBoundingSphere();
    computeVertexNormals();
}

void VertexBuffer::computeBoundingSphere()
{
    vector<math::vec3> points;
    for (size_t i = 0; i < m_vertices.size(); i++)
        points.push_back(m_vertices[i].p);

    m_boundingSphere.calculate(points);
}

void VertexBuffer::computeVertexNormals()
{
    vector<int> polysTouchVertex(m_vertices.size());

    switch(m_type)
    {
    case INDEXEDTRIANGLELIST:

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

    case TRIANGLELIST:

        syslog << "Unsupported" << logerr;
        break;

        for(size_t v = 0; v < m_vertices.size(); v += 3)
        {
            if ((v + 2) >= m_vertices.size())
                break;

        }
        break;

    case LINELIST:
        break;

    case UNDEFINED:
    default:
        syslog << "Undefined mesh type" << logwarn;
        break;
    }
}

}
