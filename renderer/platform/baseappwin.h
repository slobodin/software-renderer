/*
 * baseappwin.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef BASEAPPWIN_H
#define BASEAPPWIN_H

#include "baseapp.h"
#include "rend/viewport.h"

DECLARE_EXCEPTION(WindowsException)

namespace platform
{

class BaseAppWin : public BaseApp
{
protected:
    virtual void update(float dt) = 0;

public:
    BaseAppWin(int argc, const char **argv);
    virtual ~BaseAppWin();

    virtual LRESULT WINAPI handleMessage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

    virtual void onFrameStart() = 0;
    virtual void onFrameEnd() = 0;

    virtual void onMouseEvent(const MouseEvent &ev) = 0;

    virtual void onKeyPressed(const KeyboardEvent &ev) = 0;
    virtual void onKeyReleased(const KeyboardEvent &ev) = 0;

    virtual void onResize(int w, int h);

    int run();
};

class WindowsViewport : public rend::Viewport
{
    HWND m_hWnd;
    HDC  m_hDC;

public:
    WindowsViewport(int width, int height, sptr(rend::Camera) camera);
    ~WindowsViewport();

    void flush(const unsigned char *const pixels);
};

}

#endif // BASEAPPWIN_H