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

    sptr(Mesh)          getMesh();
    const sptr(Mesh)    getMesh() const;

    sptr(SceneObject)   clone();
};

}

#endif // SCENEOBJECT_H
