#include "rendermgr.h"

namespace rend
{

RenderMgr::RenderMgr(const int width, const int height)
    : m_camera(new Camera(math::vec3(), width, height)),
      m_resourceMgr(new base::ResourceMgr)
{
    m_camera->setPosition(math::vec3(0.0, 0.0, -150.0));
    m_camera->buildCamMatrix(0.0, 0.0, 0.0);
    //m_camera->buildCamMatrix(math::vec3(0.0, 0.0, -10.0), math::vec3(10.0, 5.0, 10.0));
}

RenderMgr::~RenderMgr()
{

}

void RenderMgr::update()
{
//    m_driver->beginFrame();

//    RenderObjectsIterator it = m_objects.begin();
//    while(it != m_objects.end())
//    {
//        (*it)->draw(m_driver, m_camera);

//        it++;
//    }

//    m_driver->endFrame();
}

void RenderMgr::addRenderable(const base::OsPath &path)
{
    // load resource
    SPTR(base::Resource) gettedResource = m_resourceMgr->getResource(path);
    if (!gettedResource)
        return;

    // check: is it rendering item?
    SPTR(rend::Mesh) renderItem = dynamic_pointer_cast<rend::Mesh>(gettedResource);
    if (!renderItem)
    {
        *syslog << "Can't render" << path.filePath() << logerr;
        return;
    }

    // save it
    m_meshes.push_back(renderItem);
}

}
