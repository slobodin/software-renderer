#include "rasterizer.h"

namespace rend
{

Rasterizer::Rasterizer()
{
}

void Rasterizer::draw(const SPTR(Mesh) mesh, const SPTR(Camera) cam)
{
    const vector<math::vec3> &vertices = mesh->vertices();
    list<math::vec3> vertList;

    std::copy(vertices.begin(), vertices.end(), std::back_inserter(vertList));
    cam->apply(vertList);

    switch(mesh->type())
    {
    case Mesh::MT_MESH_INDEXEDTRIANGLELIST:


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
