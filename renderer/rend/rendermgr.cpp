/*
 * rendermgr.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "rendermgr.h"

#include "vec3.h"
#include "viewport.h"
#include "camera.h"
#include "mesh.h"
#include "light.h"
#include "sceneobject.h"
#include "guiobject.h"
#include "software/softwarerenderer.h"
#include "opengl/openglrenderer.h"

namespace rend
{

RenderMgr::RenderMgr(const shared_ptr<Camera> cam, const shared_ptr<Viewport> viewport, RendererMode mode)
    : m_camera(cam),
      m_viewport(viewport)
{
    m_camera->setEulerAnglesRotation(0, 0, 0);

    switch (mode)
    {
    case RM_SOFTWARE:
        m_renderer = make_shared<SoftwareRenderer>(viewport->getWidth(), viewport->getHeight());
        break;

    case RM_OPENGL:
        m_renderer = make_shared<OpenGLRenderer>(viewport);
        break;

    default:
        throw RenderMgrException("Unknown renderer");
    }

    // add standart white ambient light
//    addAmbientLight(Color3(255 * 0.3, 255 * 0.3, 255 * 0.3));
}

void rend::RenderMgr::makeLight()
{

}

RenderMgr::~RenderMgr()
{

}

FrameInfo RenderMgr::update()
{
    RenderList renderList;
    FrameInfo frInfo;

    if (!m_viewport)
    {
        syslog << "Viewport is not setted" << logdebug;
        return frInfo;
    }

    // 1. Clear buffer.
    m_renderer->beginFrame(m_viewport);

    // 2. Cull full meshes and form triangles render list.
    // Also applies world transformation.
    for (auto obj : m_sceneObjects)
    {
        if (!obj)
            continue;

        if (!m_camera->culled(*obj))
            renderList.append(*obj);
    }

    frInfo.trianglesOnFrameStart = renderList.getSize();

    // 3. Cull backfaces.
    renderList.removeBackfaces(m_camera);

    // 4. Lighting.
    for (auto light : m_lights)
        light->illuminate(renderList);

    // 5. World -> Camera transformation. Also cull triangles with negative Z.
    // TODO: frustum culling here.
    m_camera->toCamera(renderList);

    // 6. Sort triangles by painter algorithm.
    renderList.zsort();

    // 7. Camera -> Perspective -> Screen transformation.
    m_camera->toScreen(renderList, *m_viewport);

    frInfo.trianglesForRaster = renderList.getSize();

    // 8. Rasterize world triangles.
    m_renderer->renderWorld(renderList);

    // 9. Render post effects.
    m_renderer->renderGui(m_guiObjects);

    // 10. Flush buffer to the screen.
    m_renderer->endFrame(m_viewport);

    return frInfo;
}

sptr(AmbientLight) RenderMgr::addAmbientLight(Color3 intensity)
{
    sptr(Light) newLight;
    try
    {
        newLight = make_shared<AmbientLight>(intensity);
        m_lights.push_back(newLight);
    }
    catch(LightException)
    {
        syslog << "Light limit is reached" << logerr;
        return dynamic_pointer_cast<AmbientLight>(sptr(Light)());
    }

    return dynamic_pointer_cast<AmbientLight>(newLight);
}

sptr(DirectionalLight) RenderMgr::addDirectionalLight(rend::Color3 intensity, math::vec3 direction)
{
    sptr(Light) newLight;
    try
    {
        newLight = make_shared<DirectionalLight>(intensity, direction);
        m_lights.push_back(newLight);
    }
    catch(LightException)
    {
        syslog << "Light limit is reached" << logerr;
        return dynamic_pointer_cast<DirectionalLight>(sptr(Light)());
    }

    return dynamic_pointer_cast<DirectionalLight>(newLight);
}

sptr(PointLight) RenderMgr::addPointLight(Color3 intensity, math::vec3 position,
                                          double kc, double kl, double kq)
{
    sptr(Light) newLight;
    try
    {
        newLight = make_shared<PointLight>(intensity, position, kc, kl, kq);
        m_lights.push_back(newLight);
    }
    catch(LightException)
    {
        syslog << "Light limit is reached" << logerr;
        return dynamic_pointer_cast<PointLight>(sptr(Light)());
    }

    return dynamic_pointer_cast<PointLight>(newLight);
}

void RenderMgr::resize(int w, int h)
{
    m_viewport->resize(w, h);
    m_renderer->resize(w, h);
}

void RenderMgr::addSceneObject(sptr(SceneObject) node)
{
    if (!node)
    {
        syslog << "Trying to add empty object" << logerr;
        return;
    }

    m_sceneObjects.push_back(node);

    // TODO: check names
}

sptr(SceneObject) RenderMgr::getSceneObject(const string &name)
{
    auto obj = std::find_if(m_sceneObjects.begin(), m_sceneObjects.end(),
                            [&](sptr(SceneObject) val)
                            { return val->getName() == name; } );

    if (obj == m_sceneObjects.end())
        return sptr(SceneObject)();

    return *obj;
}

void RenderMgr::addGuiObject(sptr(GuiObject) obj)
{
    m_guiObjects.push_back(obj);
}

sptr(Light) RenderMgr::getLight(int id) const
{
    auto obj = std::find_if(m_lights.begin(), m_lights.end(),
                            [&](sptr(Light) val)
                            { return val->getId() == id; } );

    if (obj == m_lights.end())
        return sptr(Light)();

    return *obj;
}

sptr(Light) RenderMgr::getFirstPointLight() const
{
    for (auto light : m_lights)
    {
        if (dynamic_pointer_cast<PointLight>(light))
            return dynamic_pointer_cast<PointLight>(light);
    }

    return sptr(Light)();
}

}
