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

void Mesh::computeBoundingSphere(const math::M44 &transform)
{
    int sz = 0;

    for (auto &vb : m_submeshes)
        sz += vb.numVertices();

    vector<math::vec3> points(sz);

    int j = 0;
    for (auto &vb : m_submeshes)
    {
        for (size_t i = 0; i < vb.m_vertices.size(); i++, j++)
            points[j] = vb.m_vertices[i].p;
    }

    // apply transformation
    const math::M33 &rotsc = transform.getM();
    std::for_each(points.begin(), points.end(), [&](math::vec3 &v) { v = v * rotsc; });

    m_boundingSphere.calculate(points);
}

const BoundingSphere &Mesh::getBoundingSphere() const
{
    return m_boundingSphere;
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

int Mesh::numTriangles() const
{
    // TODO: do not compute count of triangles every time.
    int trianglesCount = 0;

    for (auto &vb : m_submeshes)
    {
        switch (vb.getType())
        {
        case VertexBuffer::INDEXEDTRIANGLELIST:
            trianglesCount += vb.numIndices() / 3;
            break;

        case VertexBuffer::TRIANGLELIST:
            trianglesCount += vb.numVertices() / 3;
            break;

        default:
            break;
        }
    }

    return trianglesCount;
}

void Mesh::setShadingMode(Material::ShadeMode shMode)
{
    for (auto &vb : m_submeshes)
        vb.getMaterial()->shadeMode = shMode;      // ?
}

void Mesh::setTexture(sptr(Texture) texture)
{
    for (auto &vb : m_submeshes)
    {
        vb.getMaterial()->texture = texture;      // ?
        vb.getMaterial()->shadeMode = Material::SM_TEXTURE;
    }
}

void Mesh::setSideType(Material::SideType side)
{
    for (auto &vb : m_submeshes)
        vb.getMaterial()->sideType = side;      // ?
}

sptr(Mesh) Mesh::clone() const
{
    sptr(Mesh) objMesh = make_shared<Mesh>();

    for (auto &submesh : m_submeshes)
    {
        VertexBuffer vb;
        vb.m_type = submesh.m_type;
        vb.m_material = submesh.m_material->clone();
        vb.m_vertices = submesh.m_vertices;
        vb.m_indices = submesh.m_indices;
        vb.m_uvs = submesh.m_uvs;
        vb.m_uvsIndices = submesh.m_uvsIndices;

        objMesh->appendSubmesh(vb);
    }

    return objMesh;
}

}
