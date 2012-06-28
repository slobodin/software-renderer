/*
 * unixapplication.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef UNIXAPPLICATION_H
#define UNIXAPPLICATION_H

#include "renderer.h"
#include <X11/Xlib.h>

DECLARE_EXCEPTION(XServerException)

class UnixApplication : public platform::BaseApp
{
    Display *d;

public:
    UnixApplication();    
    virtual ~UnixApplication();

    virtual void onFrameStart();
    virtual void onFrameEnd();

    virtual void onMouseEvent(const MouseEvent &ev);

    virtual void onKeyPressed(int keycode);
    virtual void onKeyReleased(int keycode);

    virtual void onResize(int w, int h);

    virtual int run();
};

#endif // UNIXAPPLICATION_H
