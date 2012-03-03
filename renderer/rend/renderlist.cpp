#include "renderlist.h"

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

        for(size_t ind = 0; ind < mesh.numIndices(); ind += 3)
        {
            if ((ind + 2) == mesh.numIndices())
                break;

            triangle.v(0) = vertices[indices[ind]];
            triangle.v(1) = vertices[indices[ind + 1]];
            triangle.v(2) = vertices[indices[ind + 2]];

            m_triangles.push_back(triangle);
        }
        break;

    case Mesh::MT_MESH_TRIANGLELIST:

        break;

    case Mesh::MT_MESH_UNDEFINED:
    default:
        *syslog << "Can't draw this mesh" << logwarn;
        break;
    }
}

}
