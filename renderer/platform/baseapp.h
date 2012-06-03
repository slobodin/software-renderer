/*
 * BaseApp.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef BASEAPP_H
#define BASEAPP_H

#include "comm_pch.h"

namespace base
{
class Controller;
}

class DLL_PUBLIC BaseApp
{
    sptr(base::Controller) m_clientController;

public:
    BaseApp() { }
    virtual ~BaseApp() { }

    virtual void setupRenderingContext(const string &windowTitle) = 0;

    virtual void onFrameStart() = 0;
    virtual void onFrameEnd() = 0;

    virtual void onMouseMotion(int dx, int dy) = 0;
    virtual void onMouseLeftPressed(int x, int y) = 0;
    virtual void onMouseLeftReleased(int x, int y) = 0;
    virtual void onMouseRightPressed(int x, int y) = 0;
    virtual void onMouseRightReleased(int x, int y) = 0;

    virtual void onKeyPressed(int keycode) = 0;
    virtual void onKeyReleased(int keycode) = 0;

    virtual void run() = 0;
};

#endif // BASEAPP_H
