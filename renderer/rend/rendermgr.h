/*
 * rendermgr.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef RENDERMGR_H
#define RENDERMGR_H

#include "comm_pch.h"

#include "camera.h"
#include "rasterizer.h"
#include "mesh.h"
#include "light.h"
#include "renderdevice.h"

namespace rend
{

class RenderMgr : boost::noncopyable
{
    sptr(Rasterizer) m_rasterizer;
    sptr(Camera) m_camera;

    vector<sptr(Mesh) > m_meshes;
    vector<sptr(Light) > m_lights;

    // helpers
    void makeLight();

public:
    RenderMgr(const shared_ptr<Camera> cam);
    ~RenderMgr();

    void update(sptr(RenderDevice) rendDevice);

    // TODO: make uniform method `addSceneObject(Node *n);'
    void addMesh(sptr(rend::Mesh) mesh);
    sptr(AmbientLight) addAmbientLight(Color3 intensity);
    sptr(DirectionalLight) addDirectionalLight(Color3 intensity, math::vec3 direction);
    sptr(PointLight) addPointLight(Color3 intensity, math::vec3 position /* Coeffs */);

    void resize(int w, int h);
};

}

#endif // RENDERMGR_H
