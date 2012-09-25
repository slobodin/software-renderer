/*
 * sceneobject.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "sceneobject.h"

#include "mesh.h"
#include "resourcemgr.h"
#include "texture.h"

namespace rend
{

SceneObject::SceneObject(sptr(Mesh) mesh)
    : m_mesh(mesh)
{
    m_mesh->computeBoundingSphere(m_worldTransformation);
}

SceneObject::~SceneObject()
{
}

BoundingSphere SceneObject::bsphere() const
{
    if (!m_mesh)
        return BoundingSphere();        // return invalid sphere.

    return m_mesh->getBoundingSphere();
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

void SceneObject::setPosition(const math::vec3 &pos)
{
    Node::setPosition(pos);
}

void SceneObject::setRotation(const math::vec3 &angles)
{
    Node::setRotation(angles);
}

void SceneObject::setRotation(double yaw, double pitch, double roll)
{
    Node::setRotation(yaw, pitch, roll);
}

void SceneObject::setScale(const math::vec3 &coeff)
{
    Node::setScale(coeff);

    // sphere changes only when we scaling the object.
    m_mesh->computeBoundingSphere(m_worldTransformation);
}

void SceneObject::setTransformation(const math::M44 &tr)
{
    Node::setTransformation(tr);

    // sphere changes only when we scaling the object.
    m_mesh->computeBoundingSphere(m_worldTransformation);
}

void SceneObject::additionalLoading(base::ResourceMgr *const rm)
{
    auto &vbs = m_mesh->getSubmeshes();

    for (auto &vb : vbs)
    {
        auto material = vb.getMaterial();
        if (material->textureName.empty())
            continue;

        material->texture = rm->getObject<rend::Texture>(material->textureName);
    }
}

void SceneObject::setMesh(sptr(Mesh) mesh)
{
    if (!mesh)
    {
        syslog << "Trying to set empty mesh." << logerr;
        return;
    }

    m_mesh = mesh;
    m_mesh->computeBoundingSphere(m_worldTransformation);
}

}
