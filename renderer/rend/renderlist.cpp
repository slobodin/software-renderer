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

void RenderList::createTriangles(const VertexBuffer &vertexBuffer, const math::M44 &transform)
{
    math::Triangle triangle;
    // all mesh vertices
    const VertexBuffer::VertexArray &vertices = vertexBuffer.getVertices();
    // mesh indices
    const VertexBuffer::IndexArray &indices = vertexBuffer.getIndices();

    const vector<math::vec2> &uvs = vertexBuffer.getUVs();
    const VertexBuffer::IndexArray &uvind = vertexBuffer.getUVIndices();

    size_t verticesSize = vertices.size();
    size_t indicesSize = indices.size();
    size_t t = m_lastTriangleIndex;

    switch(vertexBuffer.getType())
    {
    case VertexBuffer::INDEXEDTRIANGLELIST:

        for(size_t ind = 0; ind < indicesSize; ind += 3, t++)
        {
            if ((ind + 2) >= indicesSize)
                break;

            // form the triangle
            triangle.v(0) = vertices[indices[ind]];
            triangle.v(1) = vertices[indices[ind + 1]];
            triangle.v(2) = vertices[indices[ind + 2]];

            // translate and rotate the triangle
            // TODO: applying transformation for normals only where changing matrix (do not need store original normals)
            triangle.applyTransformation(transform);

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
            m_triangles[t] = triangle;
//            m_triangles.push_back(triangle);
        }

        m_lastTriangleIndex += t;

        break;

    case VertexBuffer::TRIANGLELIST:

        for(size_t v = 0; v < verticesSize; v += 3, t++)
        {
            if ((v + 2) >= verticesSize)
                break;

            // form the triangle
            triangle.setVertices(&vertices[v]);

            // translate and rotate the triangle
            triangle.applyTransformation(transform);                    // bottleneck

            // set material
            triangle.setMaterial(vertexBuffer.getMaterial());

            // compute normals
            triangle.computeNormal();                                   // bottleneck

            // save it
//            m_triangles.push_back(triangle);                            // bottleneck
            m_triangles[t] = triangle;
        }

        m_lastTriangleIndex += t;

        break;

    case VertexBuffer::UNDEFINED:
    default:
        syslog << "Can't draw this mesh." << logerr;
        break;
    }
}

void RenderList::prepare(int trianglesCount)
{
//    m_triangles.clear();
    m_lastTriangleIndex = 0;
    if (m_triangles.size() < trianglesCount)
    {
        m_triangles.resize(trianglesCount);
    }
}

void RenderList::append(const SceneObject &obj)
{
    if (!obj.getMesh())
        return;

    const list<VertexBuffer> &subMeshes = obj.getMesh()->getSubmeshes();
    math::M44 worldTransform = obj.getTransformation();

    for (const auto &vb : subMeshes)
    {
        // TODO: where to compute vertex normals? Here?? Maybe when we apply transformation for model only?
        createTriangles(vb, worldTransform);
    }
}

void RenderList::zsort()
{
//    m_triangles.sort(math::ZCompareAvg);
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

        if (t->getMaterial()->sideType == rend::Material::TWO_SIDE)
        {
            t++;
            continue;
        }

        math::vec3 view = cam->getPosition() - t->v(0).p;
        view.normalize();
        float dp = t->normal().dotProduct(view);

        if (dp <= 0)
        {
            // TODO:
            // not erase, just flag it as culled
            t->clipped = true;
//            t = m_triangles.erase(t);
//            continue;
        }

        t++;
    }
}

}
