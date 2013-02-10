/*
 * sceneobject.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "node.h"
#include "../base/resource.h"
#include "boundingsphere.h"

namespace base { class ResourceMgr; }

namespace rend
{

class Mesh;

class SceneObject : public Node, public base::Resource
{
    sptr(Mesh) m_mesh;

public:
    SceneObject() { }
    SceneObject(sptr(Mesh) mesh);
    ~SceneObject();

    void                setMesh(sptr(Mesh) mesh);

    BoundingSphere      bsphere() const;

    sptr(Mesh)          getMesh();
    const sptr(Mesh)    getMesh() const;

    sptr(SceneObject)   clone() const;

    virtual void setPosition(const math::vec3 &pos);
    virtual void setRotation(const math::vec3 &angles);
    virtual void setRotation(float yaw, float pitch, float roll);
    virtual void setScale(const math::vec3 &coeff);
    virtual void setTransformation(const math::M44 &tr);

    void additionalLoading(base::ResourceMgr * const rm);

private:
    SceneObject(const SceneObject &);
    SceneObject &operator= (const SceneObject &);
};

}

#endif // SCENEOBJECT_H
