/*
 * unixapplication.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "unixapplication.h"
#include <cstdlib>

UnixApplication::UnixApplication()
    : d(0)
{
    d = XOpenDisplay(getenv("DISPLAY"));
    if (!d)
        throw XServerException("Can't connect to X Server");
}

UnixApplication::~UnixApplication()
{
    if (d)
        XCloseDisplay(d);
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
