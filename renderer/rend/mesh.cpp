/*
 * mesh.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "mesh.h"

#include "m33.h"
#include "renderlist.h"
#include "vertexbuffer.h"

namespace rend
{

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void Mesh::appendSubmesh(const VertexBuffer &submesh)
{
    m_submeshes.push_back(submesh);
}

int Mesh::numVertices() const
{
    int n = 0;
    std::for_each(m_submeshes.begin(), m_submeshes.end(),
                  [&](const VertexBuffer &buffer) { n += buffer.numVertices(); });

    return n;
}

int Mesh::numSubMeshes() const
{
    return m_submeshes.size();
}

sptr(Mesh) Mesh::clone() const
{
    sptr(Mesh) objMesh = make_shared<Mesh>();

    for (auto &submesh : m_submeshes)
    {
        VertexBuffer vb;
        vb.m_boundingSphere = submesh.m_boundingSphere;
        vb.m_type = submesh.m_type;
        vb.m_material = submesh.m_material;
        vb.m_vertices = submesh.m_vertices;
        vb.m_indices = submesh.m_indices;

        objMesh->appendSubmesh(vb);
    }

    return objMesh;
}

}
