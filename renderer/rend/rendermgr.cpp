#include "rendermgr.h"

namespace rend
{

RenderMgr::RenderMgr(const SPTR(Camera) cam)
    : m_rasterizer(new Rasterizer(cam->width(), cam->height())),
      m_camera(cam)
{
    m_camera->setPosition(math::vec3(0.0, 0.0, -150.0));
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
        m_rasterizer->draw(*mit, m_camera);
        mit++;
    }

    m_rasterizer->endFrame(m_tkCanvasName);
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
