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

namespace platform
{

struct MouseEvent;
struct KeyboardEvent;

// TODO: make it singletone. Cause we need to call static functions, that will call member functions.

class BaseApp
{
protected:
    sptr(base::Controller) m_clientController;

    static void exit() { ::exit(0); }

public:
    BaseApp();
    virtual ~BaseApp();

    virtual void onFrameStart() = 0;
    virtual void onFrameEnd() = 0;

    virtual void onMouseEvent(const MouseEvent &ev) = 0;

    virtual void onKeyPressed(const KeyboardEvent &ev) = 0;
    virtual void onKeyReleased(const KeyboardEvent &ev) = 0;

    virtual void onResize(int w, int h) = 0;

    // TODO: rename to run frame
    virtual int run();
};

}

#endif // BASEAPP_H
