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
    : m_type(MT_MESH_UNDEFINED)
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


}
