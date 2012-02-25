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

    m_rasterizer->beginFrame();

    MeshIterator mit = m_meshes.begin();
    while (mit != m_meshes.end())
    {
        vector<math::vec3> vertList;
        std::copy((*mit)->vertices().begin(), (*mit)->vertices().end(), std::back_inserter(vertList));
        m_camera->apply(vertList);

        RasterizerList list = { vertList, (*mit)->indices(), (*mit)->type(), (*mit)->materials() };
        m_rasterizer->rasterize(list);

        mit++;
    }

    m_rasterizer->endFrame(m_tkCanvasName);
}

void rend::RenderMgr::addLight(const Light::LightType &type, const math::vec3 pos, const math::vec3 &dir)
{
    SPTR(Light) newLight;
    try
    {
        newLight = SPTR(Light)(new Light(type, pos, dir));
        m_lights.push_back(newLight);
    }
    catch(LightException)
    {
        *syslog << "Light limit is reached" << logerr;
    }
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
