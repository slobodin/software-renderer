/*
 * unixapplication.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef UNIXAPPLICATION_H
#define UNIXAPPLICATION_H

#include "renderer.h"

class XViewport;

class UnixApplication : public platform::BaseApp
{
    sptr(rend::Camera) m_playerCamera;
    sptr(XViewport) m_viewport;

public:
    UnixApplication(int argc, const char *argv[]);
    virtual ~UnixApplication();

    virtual void onFrameStart();
    virtual void onFrameEnd();

    virtual void onMouseEvent(const platform::MouseEvent &ev);

    virtual void onKeyPressed(const platform::KeyboardEvent &ev);
    virtual void onKeyReleased(const platform::KeyboardEvent &ev);

    virtual void onResize(int w, int h);

    virtual int run();
};

#endif // UNIXAPPLICATION_H
