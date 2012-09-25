/*
 * renderlist.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "renderlist.h"
#include "m44.h"
#include "camera.h"
#include "vertex.h"
#include "vertexbuffer.h"
#include "mesh.h"
#include "sceneobject.h"

namespace rend
{

void RenderList::createTriangles(const VertexBuffer &vertexBuffer, const math::M44 &transform, list<math::Triangle> &output)
{
    math::Triangle triangle;
    // all mesh vertices
    auto vertices = vertexBuffer.getVertices();
    // mesh indices
    auto indices = vertexBuffer.getIndices();

    auto uvs = vertexBuffer.getUVs();
    auto uvind = vertexBuffer.getUVIndices();

    switch(vertexBuffer.getType())
    {
    case VertexBuffer::INDEXEDTRIANGLELIST:

        for(size_t ind = 0, t = 0; ind < indices.size(); ind += 3, t++)
        {
            if ((ind + 2) >= indices.size())
                break;

            // form the triangle
            triangle.v(0) = vertices[indices[ind]];
            triangle.v(1) = vertices[indices[ind + 1]];
            triangle.v(2) = vertices[indices[ind + 2]];

            // translate and rotate the triangle
            triangle.v(0).p = triangle.v(0).p * transform;
            triangle.v(1).p = triangle.v(1).p * transform;
            triangle.v(2).p = triangle.v(2).p * transform;

            if (!uvs.empty() && !uvind.empty())
            {
                triangle.v(0).t = uvs[uvind[ind]];
                triangle.v(1).t = uvs[uvind[ind + 1]];
                triangle.v(2).t = uvs[uvind[ind + 2]];
            }

            // set material
            triangle.setMaterial(vertexBuffer.getMaterial());

            // compute normal for triangle
            triangle.computeNormal();

            // save it
            output.push_back(triangle);
        }
        break;

    case VertexBuffer::TRIANGLELIST:

        for(size_t v = 0; v < vertices.size(); v += 3)
        {
            if ((v + 2) >= vertices.size())
                break;

            // form the triangle
            triangle.v(0) = vertices[v];
            triangle.v(1) = vertices[v + 1];
            triangle.v(2) = vertices[v + 2];

            // translate and rotate the triangle
            triangle.v(0).p = triangle.v(0).p * transform;
            triangle.v(1).p = triangle.v(1).p * transform;
            triangle.v(2).p = triangle.v(2).p * transform;

            // set material
            triangle.setMaterial(vertexBuffer.getMaterial());

            // compute normals
            triangle.computeNormal();

            // save it
            output.push_back(triangle);
        }
        break;

    case VertexBuffer::UNDEFINED:
    default:
        syslog << "Can't draw this mesh." << logerr;
        break;
    }
}

void RenderList::append(const SceneObject &obj)
{
    if (!obj.getMesh())
        return;

    const list<VertexBuffer> &subMeshes = obj.getMesh()->getSubmeshes();
    math::M44 worldTransform = obj.getTransformation();

    /*size_t trianglesCount = 0;

    for (auto &vb : subMeshes)
    {
        switch (vb->getType())
        {
        case VertexBuffer::INDEXEDTRIANGLELIST:
            trianglesCount += vertexBuffer.getIndices() / 3;
            break;

        case VertexBuffer::TRIANGLELIST:
            trianglesCount += vertexBuffer.getVertices() / 3;
            break;

        default:
            break;
        }
    }*/

    for (const auto &vb : subMeshes)
    {
        // TODO: where to compute vertex normals? Here?? Maybe when we apply transformation for model only?
        RenderList::createTriangles(vb, worldTransform, m_triangles);
    }
}

void RenderList::zsort()
{
    m_triangles.sort(math::ZCompareAvg);
}

void RenderList::removeBackfaces(const sptr(Camera) cam)
{
    auto t = m_triangles.begin();

    while (t != m_triangles.end())
    {
        if (t->normal().isZero())
        {
            t++;
            continue;
        }

        if (t->getSideType() == rend::Material::TWO_SIDE)
        {
            t++;
            continue;
        }

        math::vec3 view = cam->getPosition() - t->v(0).p;
        view.normalize();
        double dp = t->normal().dotProduct(view);

        if (dp <= 0)
        {
            t = m_triangles.erase(t);
            continue;
        }

        t++;
    }
}

}
