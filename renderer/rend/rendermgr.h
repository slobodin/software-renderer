/*
 * rendermgr.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef RENDERMGR_H
#define RENDERMGR_H

#include "comm_pch.h"

#include "color.h"
#include "vec3.h"

namespace rend
{

class Camera;
class Rasterizer;
class Mesh;
class Light;
class Viewport;
class AmbientLight;
class DirectionalLight;
class PointLight;

class RenderMgr : boost::noncopyable
{
    sptr(Rasterizer) m_rasterizer;
    sptr(Camera) m_camera;
    sptr(Viewport) m_viewport;

    vector<sptr(Mesh) > m_meshes;
    vector<sptr(Light) > m_lights;

    // helpers
    void makeLight();

public:
    RenderMgr(const shared_ptr<Camera> cam, const shared_ptr<Viewport> viewport);
    ~RenderMgr();

    void update(/*sptr(RenderDevice) rendDevice*/);

    // TODO: make uniform method `addSceneObject(Node *n);'
    void addMesh(sptr(rend::Mesh) mesh);
    void addViewport();

    // void setAmbientLight(color);
    // light* addLight....



    sptr(AmbientLight)      addAmbientLight(Color3 intensity);
    sptr(DirectionalLight)  addDirectionalLight(Color3 intensity, math::vec3 direction);
    sptr(PointLight)        addPointLight(Color3 intensity, math::vec3 position /* Coeffs */);

    void resize(int w, int h);
};

}

#endif // RENDERMGR_H
