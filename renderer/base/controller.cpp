/*
 * controller.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "controller.h"

#include "vec3.h"
#include "config.h"
#include "rendermgr.h"
#include "resourcemgr.h"
#include "viewport.h"
#include "camera.h"

namespace base
{

void Controller::resize(int w, int h)
{
    if (m_rendmgr)
        m_rendmgr->resize(w, h);
}

Controller::Controller(int argc, const char *argv[])
    : m_resourceMgr(new ResourceMgr),
      m_controllerConfig(0)
{
    // load config file
    string workingDir = argc > 1 ? argv[1] : "";
    m_controllerConfig = new Config(workingDir);

    // get cam position from the file (or set default)
    math::vec3 camPosition = m_controllerConfig->getRendererConfig().camPosition;
    syslog << "Initial camera position :" << camPosition << logmess;

    // create main camera
    m_mainCam = make_shared<rend::Camera>(camPosition);

    // notify rmgr about resource path. Thus it will can load resources from this path
    m_resourceMgr->addPath(m_controllerConfig->getRendererConfig().pathToTheAssets);
    m_resourceMgr->listPath();

    // load all loadable from assets path
    m_resourceMgr->loadResources();

    // learn about scene objects (read from the config file)

    // get them all from the resource manager

    // and add to the rendering container
}

Controller::~Controller()
{
    if (m_controllerConfig)
        delete m_controllerConfig;
}

void Controller::update()
{
    if (!m_rendmgr || !m_mainCam || !m_viewport)
    {
        syslog << "Controller uninitialized" << logerr;
        return;
    }

    // m_inputManager->capture() ???
    m_rendmgr->update();
}

std::pair<int, int> Controller::getViewportSize()
{
    return std::make_pair(m_controllerConfig->getRendererConfig().width,
                          m_controllerConfig->getRendererConfig().height);
}

void Controller::createRenderManager()
{
    m_rendmgr = make_shared<rend::RenderMgr>(m_mainCam, m_viewport);
}

bool Controller::viewportExist()
{
    if (m_viewport)
    {
        syslog << "Viewport already setted" << logwarn;
        return true;
    }

    return false;
}

sptr(rend::Camera) Controller::getCamera()
{
    return m_mainCam;
}

sptr(ResourceMgr) Controller::getResmgr()
{
    return m_resourceMgr;
}

sptr(rend::RenderMgr) Controller::getRendmgr()
{
    return m_rendmgr;
}

sptr(rend::Viewport) Controller::getViewport()
{
    return m_viewport;
}

}
