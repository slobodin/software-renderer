/*
 * renderlist.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "renderlist.h"
#include "camera.h"
#include "vertex.h"

namespace rend
{

RenderList::RenderList()
{
}

void RenderList::append(const Mesh &mesh)
{
    math::Triangle triangle;
    // all mesh vertices
    const vector<math::vertex> &vertices = mesh.vertices();
    // mesh indices
    const vector<size_t> &indices = mesh.indices();
    // mesh world transformation
    const math::AffineTransform &tr = mesh.transformation();

    switch(mesh.type())
    {
    case Mesh::MT_MESH_INDEXEDTRIANGLELIST:

        for(size_t ind = 0, t = 0; ind < mesh.numIndices(); ind += 3, t++)
        {
            if ((ind + 2) == mesh.numIndices())
                break;

            // form the triangle
            triangle.v(0) = vertices[indices[ind]];
            triangle.v(1) = vertices[indices[ind + 1]];
            triangle.v(2) = vertices[indices[ind + 2]];

            // translate and rotate the triangle
            tr.transformPoint(triangle.v(0).p);
            tr.transformPoint(triangle.v(1).p);
            tr.transformPoint(triangle.v(2).p);

            // set material
            if (!mesh.materials().empty())
                triangle.material() = mesh.materials()[t];
            else
                triangle.material() = Material(Color3(255, 0, 0), Material::SM_WIRE);

            // compute normals
            triangle.setWindingOrder(mesh.getWindingOrder());
            triangle.computeNormal();            

            // save it
            m_triangles.push_back(triangle);
        }
        break;

    case Mesh::MT_MESH_TRIANGLELIST:

        for(size_t v = 0; v < mesh.numVertices(); v += 3)
        {
            if ((v + 2) >= mesh.numVertices())
                break;

            triangle.v(0) = vertices[v];
            triangle.v(1) = vertices[v + 1];
            triangle.v(2) = vertices[v + 2];

            triangle.material() = Material(Color3(255, 0, 0), Material::SM_FLAT);

            triangle.setWindingOrder(mesh.getWindingOrder());
            triangle.computeNormal();            

            m_triangles.push_back(triangle);
        }
        break;

    case Mesh::MT_MESH_UNDEFINED:
    default:
        *syslog << "Can't draw this mesh" << logwarn;
        break;
    }
}

void RenderList::zsort()
{
    m_triangles.sort(math::ZCompareAvg);
}

void RenderList::removeBackfaces(const sptr(Camera) cam)
{
    list<math::Triangle>::iterator t = m_triangles.begin();

    while (t != m_triangles.end())
    {
        if (t->normal().isZero())
        {
            t++;
            continue;
        }

        if (t->getSideType() == math::Triangle::ST_2_SIDED)
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
