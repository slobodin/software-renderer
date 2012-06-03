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

namespace rend
{

class Mesh;

class DLL_PUBLIC SceneObject : public Node
{
    sptr(Mesh) m_mesh;

public:
    SceneObject(sptr(Mesh) mesh);
    ~SceneObject();

    void        setMesh(sptr(Mesh) mesh);
    sptr(Mesh)  getMesh();
};

}

#endif // SCENEOBJECT_H
