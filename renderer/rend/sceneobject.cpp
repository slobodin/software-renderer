/*
 * sceneobject.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "sceneobject.h"

#include "mesh.h"

namespace rend
{

SceneObject::SceneObject(sptr(Mesh) mesh)
    : m_mesh(mesh)
{
}

SceneObject::~SceneObject()
{
}

sptr(Mesh) SceneObject::getMesh()
{
    return m_mesh;
}

void SceneObject::setMesh(sptr(Mesh) mesh)
{
    if (!mesh)
    {
        *syslog << "Trying to set empty mesh." << logerr;
        return;
    }

    m_mesh = mesh;
}

}
