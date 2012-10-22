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

void VertexBuffer::appendVertices(const vector<math::vertex> &vertices, const vector<int> &indices,
                                  const vector<math::vec2> &uvs, const vector<int> &uvinds)
{
    std::copy(uvs.begin(), uvs.end(), std::back_inserter(m_uvs));
    std::copy(uvinds.begin(), uvinds.end(), std::back_inserter(m_uvsIndices));

    appendVertices(vertices, indices);
}

void VertexBuffer::appendVertices(const vector<math::vertex> &vertices, const vector<int> &indices)
{
    std::copy(vertices.begin(), vertices.end(), std::back_inserter(m_vertices));
    std::copy(indices.begin(), indices.end(), std::back_inserter(m_indices));

    computeVertexNormals();
}

void VertexBuffer::appendVertices(const vector<math::vertex> &vertices)
{
    std::copy(vertices.begin(), vertices.end(), std::back_inserter(m_vertices));

    computeVertexNormals();
}

void VertexBuffer::computeVertexNormals()
{
    vector<int> polysTouchVertex(m_vertices.size());

    // clear normals for all vertices
    std::for_each(m_vertices.begin(), m_vertices.end(), [](math::vertex &v) { v.n.zero(); } );

    switch(m_type)
    {
    case INDEXEDTRIANGLELIST:

        for(size_t ind = 0; ind < m_indices.size(); ind += 3)
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

        for(size_t vind = 0; vind < m_vertices.size(); vind += 3)
        {
            if ((vind + 2) >= m_vertices.size())
                break;

            polysTouchVertex[vind]++;
            polysTouchVertex[vind + 1]++;
            polysTouchVertex[vind + 2]++;

            math::vec3 u = m_vertices[vind + 1].p - m_vertices[vind].p;
            math::vec3 v = m_vertices[vind + 2].p - m_vertices[vind].p;

            math::vec3 normal = u.crossProduct(v);

            m_vertices[vind].n += normal;
            m_vertices[vind + 1].n += normal;
            m_vertices[vind + 2].n += normal;
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

    case LINELIST:
        break;

    case UNDEFINED:
    default:
        syslog << "Undefined mesh type" << logwarn;
        break;
    }
}

}
