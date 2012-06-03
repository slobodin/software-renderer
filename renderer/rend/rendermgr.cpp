/*
 * rendermgr.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "rendermgr.h"

#include "vec3.h"

namespace rend
{

RenderMgr::RenderMgr(const shared_ptr<Camera> cam)
    : m_rasterizer(new Rasterizer(cam->width(), cam->height())),
      m_camera(cam)
{
    m_camera->setPosition(math::vec3(0.0, 0.0, -450.0));
    m_camera->buildCamMatrix(0.0, 0.0, 0.0);
}

void rend::RenderMgr::makeLight()
{

}

RenderMgr::~RenderMgr()
{

}

void RenderMgr::update(sptr(RenderDevice) rendDevice)
{
    // 1. Clear buffer.
    m_rasterizer->beginFrame(rendDevice);

    RenderList renderList;

    // 2. Cull full meshes and form triangles render list.
    foreach (sptr(Mesh) m, m_meshes)
    {
        if (!m_camera->culled(*m))
            renderList.append(*m);
    }

    // 3. Cull backfaces.
    // TODO:
    renderList.removeBackfaces(m_camera);

    // 4. Lighting.
    foreach (sptr(Light) &l, m_lights)
    {
        l->illuminate(renderList);
    }

    // 5. World -> Camera transformation. Cull triangles with negative Z.
    // TODO: frustum culling here.
    m_camera->toCamera(renderList);

    // 6. Sort triangles by painter algorithm.
    renderList.zsort();

    // 7. Camera -> Perspective -> Screen transformation.
    m_camera->toScreen(renderList);

    // 8. Rasterize triangles.
    m_rasterizer->rasterize(renderList);

    // 9. Flush buffer to the screen.
    if (rendDevice)
        m_rasterizer->endFrame(rendDevice);
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
    m_camera->resize(w, h);
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
