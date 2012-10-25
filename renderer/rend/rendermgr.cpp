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

bool cmpSceneObjects(const sptr(SceneObject) o1, const sptr(SceneObject) o2)
{
    return o1->getMesh()->getSubmeshes().front().getMaterial()->alpha > o2->getMesh()->getSubmeshes().front().getMaterial()->alpha;
}

size_t RenderMgr::sceneSize() const
{
    size_t triangles = 0;
    for (auto obj : m_sceneObjects)
    {
        if (!obj)
            continue;

        triangles += obj->getMesh()->numTriangles();
    }

    return triangles;
}

RenderMgr::RenderMgr(const shared_ptr<Camera> cam, const shared_ptr<Viewport> viewport, RendererMode mode)
    : m_camera(cam),
      m_viewport(viewport),
      m_renderList(0)
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

    m_renderList = new RenderList();

    // add standart white ambient light
//    addAmbientLight(Color3(255 * 0.3, 255 * 0.3, 255 * 0.3));
}

RenderMgr::~RenderMgr()
{
    if (m_renderList)
        delete m_renderList;
}

// TODO:
// multipass rendering?
// render transparent objects first
void RenderMgr::update()
{
    if (!m_viewport)
    {
        syslog << "Viewport is not setted" << logdebug;
        return;
    }

    // 1. Clear buffer.
    m_renderer->beginFrame(m_viewport);

    // allocate mem for the render list
    m_renderList->prepare(sceneSize());

    // 2. Cull full meshes and form triangles render list.
    // Also applies world transformation.
    for (auto obj : m_sceneObjects)
    {
        if (!obj)
            continue;

        if (!m_camera->culled(*obj))
            m_renderList->append(*obj);
    }

    // collect debug information
    m_frameInfo.trianglesOnFrameStart = m_renderList->getCountOfNotClippedTriangles();

    // 3. Cull backfaces.
    m_renderList->removeBackfaces(m_camera);

    // 4. Lighting.
    for (auto light : m_lights)
        light->illuminate(*m_renderList);

    // 5. World -> Camera transformation. Also cull triangles with negative Z.
    m_camera->toCamera(*m_renderList);

    // 6. Frustum culling.
    m_camera->frustumCull(*m_renderList);

    // 7. Sort triangles by painter algorithm.
    /* m_renderList->zsort(); do not need this (using z buffer) */

    // 8. Camera -> Perspective -> Screen transformation.
    m_camera->toScreen(*m_renderList, *m_viewport);

    m_frameInfo.trianglesForRaster = m_renderList->getCountOfNotClippedTriangles();

    // 9. Rasterize world triangles.
    m_renderer->renderWorld(*m_renderList);

    // 10. Render post effects.
    m_renderer->renderGui(m_guiObjects);

    // 11. Flush buffer to the screen.
    m_renderer->endFrame(m_viewport);
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
                                          float kc, float kl, float kq)
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
//    m_sceneObjects.sort();

    // TODO: check names
    // TODO: sort objects by alpha (of material) (when adding new object)
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
    if (!obj)
        return;
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
