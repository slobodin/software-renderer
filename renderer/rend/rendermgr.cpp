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
    //m_camera->buildCamMatrix(math::vec3(0.0, 0.0, -10.0), math::vec3(10.0, 5.0, 10.0));
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
        if (!m_camera->culled(*(*mit)))
            renderList.append(*(*mit));

        mit++;
    }

    // 3. Cull backfaces
    // TODO:

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

void RenderMgr::addLight(const Light::LightType &type, const math::vec3 pos, const math::vec3 &dir)
{
    SPTR(Light) newLight;
    try
    {
        switch (type)
        {
        case Light::LT_AMBIENT_LIGHT:
            newLight = SPTR(Light)(new AmbientLight(Color3(255, 255, 255)));

            break;

        default:
            return;
        }

        m_lights.push_back(newLight);
    }
    catch(LightException)
    {
        *syslog << "Light limit is reached" << logerr;
    }
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
