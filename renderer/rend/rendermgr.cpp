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

namespace rend
{

RenderMgr::RenderMgr(const shared_ptr<Camera> cam, const shared_ptr<Viewport> viewport)
    : m_rasterizer(new Rasterizer(viewport->getWidth(), viewport->getHeight())),
      m_camera(cam),
      m_viewport(viewport)
{
    m_camera->setPosition(math::vec3(0.0, 0.0, -450.0));
    m_camera->lookTo(math::vec3(0, 0, 0));
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
        *syslog << "Viewport is not setted" << logdebug;
        return;
    }

    // 1. Clear buffer.
    m_rasterizer->beginFrame(m_viewport);

    RenderList renderList;

    // 2. Cull full meshes and form triangles render list.
    for (auto mesh : m_meshes)
    {
        if (!m_camera->culled(*mesh))
            renderList.append(*mesh);
    }

    // 3. Cull backfaces.
    // TODO:
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
        *syslog << "Light limit is reached" << logerr;
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
        *syslog << "Light limit is reached" << logerr;
        return dynamic_pointer_cast<DirectionalLight>(sptr(Light)());
    }

    return dynamic_pointer_cast<DirectionalLight>(newLight);
}

sptr(PointLight) RenderMgr::addPointLight(rend::Color3 intensity, math::vec3 position)
{
    sptr(Light) newLight;
    try
    {
        newLight = make_shared<PointLight>(intensity, position, 0, 1, 0);
        m_lights.push_back(newLight);
    }
    catch(LightException)
    {
        *syslog << "Light limit is reached" << logerr;
        return dynamic_pointer_cast<PointLight>(sptr(Light)());
    }

    return dynamic_pointer_cast<PointLight>(newLight);
}

void RenderMgr::resize(int w, int h)
{
    m_viewport->resize(w, h);
    m_rasterizer->resize(w, h);
}

void RenderMgr::addMesh(sptr(rend::Mesh) mesh)
{
    if (!mesh)
    {
        *syslog << "Trying to add empty mesh" << logerr;
        return;
    }

    m_meshes.push_back(mesh);
}

}
