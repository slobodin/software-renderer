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
class Light;
class Viewport;
class AmbientLight;
class DirectionalLight;
class PointLight;
class SceneObject;

//! Some debug stats about a frame.
struct FrameInfo
{
    int trianglesOnFrameStart;      //
    int trianglesForRaster;
};

class RenderMgr : boost::noncopyable
{
    sptr(Rasterizer) m_rasterizer;
    sptr(Camera) m_camera;
    sptr(Viewport) m_viewport;

    list<sptr(SceneObject) > m_sceneObjects;
    list<sptr(Light) > m_lights;

    // helpers
    void makeLight();

public:
    RenderMgr(const shared_ptr<Camera> cam, const shared_ptr<Viewport> viewport);
    ~RenderMgr();

    void update();

    void addSceneObject(sptr(SceneObject) node);
    sptr(SceneObject) getSceneObject(const string &name);

    sptr(Light) getLight(int id) const;

    // test function
    sptr(Light) getFirstPointLight() const;

    sptr(AmbientLight)      addAmbientLight(Color3 intensity);
    sptr(DirectionalLight)  addDirectionalLight(Color3 intensity, math::vec3 direction);
    sptr(PointLight)        addPointLight(Color3 intensity, math::vec3 position,
                                          double kc, double kl, double kq);

    void resize(int w, int h);
};

}

#endif // RENDERMGR_H
