#include "renderlist.h"
#include "camera.h"

namespace rend
{

RenderList::RenderList()
{
}

void RenderList::append(const Mesh &mesh)
{
    math::Triangle triangle;
    const vector<math::vec3> &vertices = mesh.vertices();
    const vector<size_t> &indices = mesh.indices();

    switch(mesh.type())
    {
    case Mesh::MT_MESH_INDEXEDTRIANGLELIST:

        for(size_t ind = 0, t = 0; ind < mesh.numIndices(); ind += 3, t++)
        {
            if ((ind + 2) == mesh.numIndices())
                break;

            triangle.v(0) = vertices[indices[ind]];
            triangle.v(1) = vertices[indices[ind + 1]];
            triangle.v(2) = vertices[indices[ind + 2]];

            if (!mesh.materials().empty())
                triangle.material() = mesh.materials()[t];
            else
                triangle.material() = Material(Color3(255, 0, 0), Material::SM_WIRE);

            triangle.computeNormal();

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

void RenderList::removeBackfaces(const SPTR(Camera) cam)
{
    list<math::Triangle>::iterator t = m_triangles.begin();

    while (t != m_triangles.end())
    {
        if (t->normal().isZero())
            continue;

        double dp = t->normal().dotProduct(cam->getDirection());

        if (dp < 0)
        {
            t = m_triangles.erase(t);
            continue;
        }

        t++;
    }
}

}
