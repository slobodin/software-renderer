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
    : m_resourceMgr(new ResourceMgr)
{
    m_mainCam = make_shared<rend::Camera>(math::vec3());
}

Controller::~Controller()
{
}

void Controller::update()
{
    if (!m_rendmgr || !m_mainCam || !m_viewport)
    {
        *syslog << "Controller uninitialized" << logerr;
        return;
    }

    m_rendmgr->update();
}

void Controller::setViewport(sptr(rend::Viewport) viewport)
{
    if (m_viewport)
    {
        *syslog << "Viewport already setted" << logwarn;
        return;
    }

    m_viewport = viewport;
    m_rendmgr = make_shared<rend::RenderMgr>(m_mainCam, m_viewport);
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
