/*
 * windowsapplication.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef WINDOWSAPPLICATION_H
#define WINDOWSAPPLICATION_H

#include "renderer.h"
#include <windows.h>

class WindowsApplication : public platform::BaseApp
{
    HINSTANCE m_hInstance;
    sptr(rend::Camera) m_playerCamera;

public:
    WindowsApplication(int argc, const char **argv);
    virtual ~WindowsApplication();

    virtual void onFrameStart();
    virtual void onFrameEnd();

    virtual void onMouseEvent(const platform::MouseEvent &ev);

    virtual void onKeyPressed(const platform::KeyboardEvent &ev);
    virtual void onKeyReleased(const platform::KeyboardEvent &ev);

    virtual void onResize(int w, int h);

    virtual int run();

    HINSTANCE getAppInstance() { return m_hInstance; }
    LRESULT WINAPI handleMessage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
};

#endif // WINDOWSAPPLICATION_H
