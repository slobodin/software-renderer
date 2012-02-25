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
    LightIterator_Const l = m_lights.begin();
    while (l != m_lights.end())
    {
        (*l)->illuminate();

        l++;
    }
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
        // 1. Cull object
        // 2. Cull backfaces
        // 3. Lighting
        // 4. Camera->perspective->screen->rasterize
        // FIXME: too many memory coping
        vector<math::vec3> vertList;
        std::copy((*mit)->vertices().begin(), (*mit)->vertices().end(), std::back_inserter(vertList));
        m_camera->apply(vertList);

        RenderList list(vertList, (*mit)->indices(), (*mit)->materials(), (*mit)->type());
        m_rasterizer->rasterize(list);

        mit++;
    }

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
            newLight = SPTR(Light)(new AmbientLight(Color3(0, 0, 255)));

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
