#include "rendermgr.h"

namespace rend
{

RenderMgr::RenderMgr(const int width, const int height)
    : m_rasterizer(new Rasterizer(width, height)),
      m_camera(new Camera(math::vec3(), width, height))
{
    m_camera->setPosition(math::vec3(0.0, 0.0, -50.0));
    m_camera->buildCamMatrix(0.0, 0.0, 0.0);
    //m_camera->buildCamMatrix(math::vec3(0.0, 0.0, -10.0), math::vec3(10.0, 5.0, 10.0));
}

RenderMgr::~RenderMgr()
{

}

void RenderMgr::update()
{
    m_rasterizer->beginFrame();

    MeshIterator mit = m_meshes.begin();
    while (mit != m_meshes.end())
    {
        m_rasterizer->draw(*mit, m_camera);
        mit++;
    }

    m_rasterizer->endFrame();
}

// test
void RenderMgr::rotate(const double dx, const double dy)
{
    static double yaw, pitch;
    yaw += dx;
    pitch += dy;
    m_camera->buildCamMatrix(yaw, pitch, 0);
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
