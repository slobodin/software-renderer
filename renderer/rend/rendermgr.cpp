#include "rendermgr.h"

#include "vec3.h"

namespace rend
{

RenderMgr::RenderMgr(const SPTR(Camera) cam)
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

void RenderMgr::renderTo(const string &tkCanvas)
{
    m_tkCanvasName = tkCanvas;
}

void RenderMgr::update()
{
    if (m_tkCanvasName.empty())
        return;

    // 1. Clear buffer
    m_rasterizer->beginFrame();

    MeshIterator_Const mit = m_meshes.begin();
    RenderList renderList;

    // 2. Cull full meshes and form triangles render list
    while (mit != m_meshes.end())
    {
//        if (!m_camera->culled(*(*mit)))
            renderList.append(*(*mit));

        mit++;
    }

    // 3. Cull backfaces
    // TODO:
    renderList.removeBackfaces(m_camera);

    // 4. Lighting
    LightIterator_Const l = m_lights.begin();
    while (l != m_lights.end())
    {
        (*l)->illuminate(renderList);

        l++;
    }

    // 5. World -> Camera transformation. Cull triangles with negative Z.
    // TODO: frustum culling here
    m_camera->toCamera(renderList);

    // 6. Sort triangles by painter algorithm
    renderList.zsort();

    // 7. Camera -> Perspective -> Screen transformation
    m_camera->toScreen(renderList);

    // 8. Rasterize triangles
    m_rasterizer->rasterize(renderList);

    // 9. Flush buffer to the screen
    m_rasterizer->endFrame(m_tkCanvasName);
}

void rend::RenderMgr::addAmbientLight(Color3 intensity)
{
    SPTR(Light) newLight;
    try
    {
        newLight = SPTR(Light)(new AmbientLight(intensity));
        m_lights.push_back(newLight);
    }
    catch(LightException)
    {
        *syslog << "Light limit is reached" << logerr;
    }
}

SPTR(DirectionalLight) rend::RenderMgr::addDirectionalLight(rend::Color3 intensity, math::vec3 direction)
{
    SPTR(Light) newLight;
    try
    {
        newLight = SPTR(Light)(new DirectionalLight(intensity, direction));
        m_lights.push_back(newLight);
    }
    catch(LightException)
    {
        *syslog << "Light limit is reached" << logerr;
        return dynamic_pointer_cast<DirectionalLight>(SPTR(Light)());
    }

    return dynamic_pointer_cast<DirectionalLight>(newLight);
}

void rend::RenderMgr::resize(int w, int h)
{
    m_camera->resize(w, h);
    m_rasterizer->resize(w, h);
}

void RenderMgr::addMesh(SPTR(rend::Mesh) mesh)
{
    if (!mesh)
    {
        *syslog << "Trying to add empty mesh" << logerr;
        return;
    }

    m_meshes.push_back(mesh);
}

}
