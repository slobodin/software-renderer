/*
 * sceneobject.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "comm_pch.h"

#include "node.h"
#include "resource.h"
#include "boundingsphere.h"

namespace rend
{

class Mesh;

class SceneObject : public Node, public base::Resource
{
    sptr(Mesh) m_mesh;

public:
    SceneObject(sptr(Mesh) mesh);
    ~SceneObject();

    void                setMesh(sptr(Mesh) mesh);

    const BoundingSphere &bsphere() const;

    sptr(Mesh)          getMesh();
    const sptr(Mesh)    getMesh() const;

    sptr(SceneObject)   clone() const;

    virtual void setPosition(const math::vec3 &pos);
    virtual void setRotation(const math::vec3 &angles);
    virtual void setRotation(double yaw, double pitch, double roll);
    virtual void setScale(const math::vec3 &coeff);
    virtual void setTransformation(const math::M44 &tr);

private:
    SceneObject(const SceneObject &);
    SceneObject &operator= (const SceneObject &);
};

}

#endif // SCENEOBJECT_H
