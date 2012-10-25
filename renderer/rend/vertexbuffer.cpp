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
                                  const vector<math::vec2> &uvs, const vector<int> &uvinds,
                                  bool isNormalsComputed)
{
    std::copy(uvs.begin(), uvs.end(), std::back_inserter(m_uvs));
    std::copy(uvinds.begin(), uvinds.end(), std::back_inserter(m_uvsIndices));

    appendVertices(vertices, indices, isNormalsComputed);
}

void VertexBuffer::appendVertices(const vector<math::vertex> &vertices, const vector<int> &indices,
                                  bool isNormalsComputed)
{
    std::copy(vertices.begin(), vertices.end(), std::back_inserter(m_vertices));
    std::copy(indices.begin(), indices.end(), std::back_inserter(m_indices));

    if (!isNormalsComputed)
        computeVertexNormals();
}

void VertexBuffer::appendVertices(const vector<math::vertex> &vertices,
                                  bool isNormalsComputed)
{
    std::copy(vertices.begin(), vertices.end(), std::back_inserter(m_vertices));

    if (!isNormalsComputed)
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
        syslog << "Can't compute normals for triangle list vertex buffer" << logwarn;
        break;

        // O(n^2) !!!!!!
        for (size_t vertex = 0; vertex < m_vertices.size(); vertex++)
        {
            auto &currVertex = m_vertices[vertex];
            math::vec3 resNormal;

            // for each triangle
            for(size_t vind = 0; vind < m_vertices.size(); vind += 3)
            {
                if ((vind + 2) >= m_vertices.size())
                    break;

                if (currVertex.p == m_vertices[vind].p ||
                        currVertex.p == m_vertices[vind + 1].p ||
                        currVertex.p == m_vertices[vind + 2].p)
                {
                    math::vec3 u = m_vertices[vind + 1].p - m_vertices[vind].p;
                    math::vec3 v = m_vertices[vind + 2].p - m_vertices[vind].p;
                    math::vec3 normal = u.crossProduct(v);
                    normal.normalize();
                }
            }

            currVertex.n = resNormal.normalize();
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

bool VertexBuffer::operator< (const VertexBuffer &vb)
{
    return m_material->alpha > vb.m_material->alpha;
}

}
