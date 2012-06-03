/*
 * controller.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "controller.h"

#include "vec3.h"
#include "config.h"

namespace base
{

void Controller::resize(int w, int h)
{
    m_rendmgr->resize(w, h);
}

Controller::Controller(char *argv[])
    : m_resourceMgr(new ResourceMgr)
{
    m_mainCam = make_shared<rend::Camera>(math::vec3(), 640, 480);
    m_rendmgr = make_shared<rend::RenderMgr>(m_mainCam);

    Config config;
    config.configure(conf, this);
}

Controller::~Controller()
{
}

void Controller::update()
{
    if (!m_rendDevice)
        return;

    m_rendmgr->update(m_rendDevice);
}

}
