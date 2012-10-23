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

namespace base
{

struct FrameInfo;

}

namespace rend
{

DECLARE_EXCEPTION(RenderMgrException)

class Camera;
class AbstractRenderer;
class Light;
class Viewport;
class AmbientLight;
class DirectionalLight;
class PointLight;
class SceneObject;
class GuiObject;
class RenderList;

enum RendererMode
{
    RM_SOFTWARE,
    RM_OPENGL
};

//! Some debug stats about a frame.
struct FrameInfo
{
    int trianglesOnFrameStart;      //
    int trianglesForRaster;
};

class RenderMgr : boost::noncopyable
{
    sptr(AbstractRenderer) m_renderer;
    sptr(Camera) m_camera;
    sptr(Viewport) m_viewport;

    list<sptr(SceneObject)> m_sceneObjects;
    list<sptr(GuiObject)> m_guiObjects;
    list<sptr(Light)> m_lights;

    FrameInfo m_frameInfo;
    RenderList *m_renderList;

public:
    RenderMgr(const shared_ptr<Camera> cam, const shared_ptr<Viewport> viewport, RendererMode mode);
    ~RenderMgr();

    void update();

    void                addSceneObject(sptr(SceneObject) node);
    sptr(SceneObject)   getSceneObject(const string &name);
    void                addGuiObject(sptr(GuiObject) obj);

    const FrameInfo    &getLastFrameStats() const { return m_frameInfo; }

    sptr(Light) getLight(int id) const;

    // test function
    sptr(Light) getFirstPointLight() const;

    sptr(AmbientLight)      addAmbientLight(Color4 intensity);
    sptr(DirectionalLight)  addDirectionalLight(Color4 intensity, math::vec3 direction);
    sptr(PointLight)        addPointLight(Color4 intensity, math::vec3 position,
                                          float kc, float kl, float kq);

    void resize(int w, int h);
};

}

#endif // RENDERMGR_H
