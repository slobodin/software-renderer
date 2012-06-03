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

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void Mesh::appendSubmesh(const VertexBuffer &submesh)
{
    m_submeshes.push_back(submesh);
    m_submeshes.back().computeVertexNormals();
}

int Mesh::numVertices() const
{
    int n = 0;
    std::for_each(m_submeshes.begin(), m_submeshes.end(),
                  [&](VertexBuffer buffer) { n += buffer.numVertices(); });

    return n;
}

int Mesh::numSubMeshes() const
{
    return m_submeshes.size();
}

}
