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
#include "rasterizer.h"
#include "mesh.h"
#include "light.h"
#include "sceneobject.h"

namespace rend
{

RenderMgr::RenderMgr(const shared_ptr<Camera> cam, const shared_ptr<Viewport> viewport)
    : m_rasterizer(new Rasterizer(viewport->getWidth(), viewport->getHeight())),
      m_camera(cam),
      m_viewport(viewport)
{
    m_camera->setEulerAnglesRotation(0, 0, 0);

    // add standart white ambient light
//    addAmbientLight(Color3(255 * 0.3, 255 * 0.3, 255 * 0.3));
}

void rend::RenderMgr::makeLight()
{

}

RenderMgr::~RenderMgr()
{

}

void RenderMgr::update()
{
    if (!m_viewport)
    {
        syslog << "Viewport is not setted" << logdebug;
        return;
    }

    // 1. Clear buffer.
    m_rasterizer->beginFrame(m_viewport);

    RenderList renderList;

    // 2. Cull full meshes and form triangles render list.
    // Also applies world transformation.
    for (auto obj : m_sceneObjects)
    {
        if (!m_camera->culled(*obj))
            renderList.append(*obj);
    }

    // 3. Cull backfaces.
    renderList.removeBackfaces(m_camera);

    // 4. Lighting.
    for (auto light : m_lights)
        light->illuminate(renderList);

    // 5. World -> Camera transformation. Cull triangles with negative Z.
    // TODO: frustum culling here.
    m_camera->toCamera(renderList);

    // 6. Sort triangles by painter algorithm.
    renderList.zsort();

    // 7. Camera -> Perspective -> Screen transformation.
    m_camera->toScreen(renderList, *m_viewport);

    // 8. Rasterize triangles.
    m_rasterizer->rasterize(renderList);

    // 9. Flush buffer to the screen.
    m_rasterizer->endFrame(m_viewport);
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
    m_rasterizer->resize(w, h);
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

sptr(Light) RenderMgr::getLight(int id) const
{
    auto obj = std::find_if(m_lights.begin(), m_lights.end(),
                            [&](sptr(Light) val)
                            { return val->getId() == id; } );

    if (obj == m_lights.end())
        return sptr(Light)();

    return *obj;
}

}
