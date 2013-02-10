/*
 * rendermgr.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef RENDERMGR_H
#define RENDERMGR_H

#include "rend/color.h"
#include "math/vec3.h"

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

class RenderMgr
{
    sptr(AbstractRenderer) m_renderer;
    sptr(Camera) m_camera;
    sptr(Viewport) m_viewport;

    std::list<sptr(SceneObject)> m_sceneObjects;
    std::list<sptr(GuiObject)> m_guiObjects;
    std::list<sptr(Light)> m_lights;

    size_t m_sceneTrianglesCount;

    FrameInfo m_frameInfo;
    RenderList *m_renderList;

    //! Returns scene size in triangles.
    size_t sceneSize() const;

public:
    RenderMgr(const sptr(Camera) cam, const sptr(Viewport) viewport, RendererMode mode);
    ~RenderMgr();

    void runFrame();

    void                addSceneObject(sptr(SceneObject) node);
    sptr(SceneObject)   getSceneObject(const std::string &name);
    void                addGuiObject(sptr(GuiObject) obj);

    const FrameInfo    &getLastFrameStats() const { return m_frameInfo; }

    sptr(Light) getLight(int id) const;

    sptr(AmbientLight)      addAmbientLight(Color3 intensity);
    sptr(DirectionalLight)  addDirectionalLight(Color3 intensity, math::vec3 direction);
    sptr(PointLight)        addPointLight(Color3 intensity, math::vec3 position,
                                          float kc, float kl, float kq);

    void resize(int w, int h);

    NONCOPYABLE(RenderMgr)
};

}

#endif // RENDERMGR_H
