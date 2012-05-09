/*
 * controller.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "controller.h"

#include <third-party/cpptk-1.0.2/cpptk.h>
#include "vec3.h"
#include "config.h"

namespace base
{

using namespace Tk;

void Controller::update()
{
    m_instance->m_rendmgr->update();

    Tk::afteridle(m_instance->m_updateCallback);
}

void Controller::resize(int w, int h)
{
    m_rendmgr->resize(w, h);
}

Controller::Controller(char *argv[], const string &conf)
    : m_resourceMgr(new ResourceMgr)
{
    m_mainCam = make_shared<rend::Camera>(math::vec3(), 640, 480);
    m_rendmgr = make_shared<rend::RenderMgr>(m_mainCam);

    Config config;
    config.configure(conf, this);

    Tk::init(argv[0]);

    Tk::wm(Tk::title, ".", "Result");

    // create rendering canvas
    Tk::images(Tk::create, Tk::photo, "canvas_photo")
            -Tk::width(m_mainCam->width())
            -Tk::height(m_mainCam->height());

    Tk::frame(".canvas_frame");
    Tk::canvas(".canvas_frame.c") -Tk::highlightthickness(0)
            -Tk::width(m_mainCam->width())
            -Tk::height(m_mainCam->height());

    Tk::pack(".canvas_frame.c") -side("top");
    Tk::pack(".canvas_frame") -side("left");

    (".canvas_frame.c" << Tk::create(Tk::image, 0, 0)) -Tk::image("canvas_photo") -Tk::anchor(nw);

    m_rendmgr->renderTo("canvas_photo");

    // setup update event
    m_updateCallback = Tk::callback(&Controller::update);
    Tk::after(500, m_updateCallback);
}

Controller::~Controller()
{
}

void Controller::run()
{
    Tk::runEventLoop();
}

}
