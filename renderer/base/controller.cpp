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
    m_mainCam = make_shared<rend::Camera>(math::vec3());
    m_viewport = make_shared<rend::Viewport>(640, 480, m_mainCam);
    m_rendmgr = make_shared<rend::RenderMgr>(m_mainCam, m_viewport);

    Config config;
    config.configure(this);
}

Controller::~Controller()
{
}

void Controller::update()
{
    m_rendmgr->update();
}

}
