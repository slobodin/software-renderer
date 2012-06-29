/*
 * unixapplication.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "unixapplication.h"
#include "xviewport.h"

UnixApplication::UnixApplication(int argc, const char *argv[])
    : platform::BaseApp()
{
    m_clientController = boost::make_shared<base::Controller>(argc, argv);

    m_playerCamera = m_clientController->getCamera();

    m_clientController->setViewport(boost::make_shared<XViewport>(640, 480, m_playerCamera));
}

UnixApplication::~UnixApplication()
{
}

void UnixApplication::onFrameStart()
{
}

void UnixApplication::onFrameEnd()
{
}

void UnixApplication::onMouseEvent(const MouseEvent &ev)
{
}

void UnixApplication::onKeyPressed(int keycode)
{
}

void UnixApplication::onKeyReleased(int keycode)
{
}

void UnixApplication::onResize(int w, int h)
{
}

int UnixApplication::run()
{
}
