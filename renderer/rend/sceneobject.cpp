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

const sptr(Mesh) SceneObject::getMesh() const
{
    return m_mesh;
}

sptr(SceneObject) SceneObject::clone() const
{
    sptr(Mesh) newmesh = m_mesh->clone();
    sptr(SceneObject) newObj = make_shared<SceneObject>(newmesh);

    newObj->m_name = m_name + "_clone";
    newObj->m_worldTransformation = m_worldTransformation;

    return newObj;
}

void SceneObject::setMesh(sptr(Mesh) mesh)
{
    if (!mesh)
    {
        syslog << "Trying to set empty mesh." << logerr;
        return;
    }

    m_mesh = mesh;
}

}
