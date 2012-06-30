/*
 * windowsapplication.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "windowsapplication.h"

#include "windowsviewport.h"
#include <windows.h>

LRESULT WINAPI WindowsApplication::handleMessage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static platform::MouseEvent mouseEvent;
    static platform::KeyboardEvent keyboardEvent(0);

    switch (msg)
    {
    case WM_KEYDOWN:
        memset(&keyboardEvent, 0, sizeof(platform::KeyboardEvent));
        keyboardEvent.setKeyCode(wp);

        onKeyPressed(keyboardEvent);

        return 0;

    case WM_KEYUP:
        memset(&keyboardEvent, 0, sizeof(platform::KeyboardEvent));
        keyboardEvent.setKeyCode(wp);

        onKeyReleased(keyboardEvent);
        return 0;

    case WM_MOUSEMOVE:
        memset(&mouseEvent, 0, sizeof(platform::MouseEvent));
        mouseEvent.x = LOWORD(lp);
        mouseEvent.y = HIWORD(lp);
        mouseEvent.buttonsState = wp & (MK_LBUTTON | MK_RBUTTON);
        if (wp & MK_MBUTTON)
            mouseEvent.buttonsState |= platform::MouseEvent::MIDDLE_PRESSED;

        onMouseEvent(mouseEvent);

        return 0;

    case WM_MOUSEWHEEL:

        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_SIZE:
        m_clientController->resize(LOWORD(lp), HIWORD(lp));
        return 0;

    default:
        return DefWindowProc(hwnd, msg, wp, lp);
    }
}

WindowsApplication::WindowsApplication(int argc, const char **argv)
    : platform::BaseApp()
{
    m_hInstance = GetModuleHandle(NULL);

    m_clientController = boost::make_shared<base::Controller>(argc, argv);
    m_playerCamera = m_clientController->getCamera();

    m_clientController->setViewport(boost::make_shared<WindowsViewport>(this, 640, 480, m_playerCamera));
    m_viewport = boost::dynamic_pointer_cast<WindowsViewport>(m_clientController->getViewport());
}

WindowsApplication::~WindowsApplication()
{
}

void WindowsApplication::onFrameStart()
{
}

void WindowsApplication::onFrameEnd()
{
}

void WindowsApplication::onMouseEvent(const platform::MouseEvent &ev)
{
    if (ev.isLeftPressed())
        std::cerr << "Left pressed\n";
    if (ev.isRightPressed())
        std::cerr << "Right pressed\n";
    if (ev.isMiddlePressed())
        std::cerr << "Middle pressed\n";

    std::cerr << "x: " << ev.x << " y: " << ev.y << "\n";

    /*if (dx || dy > 0)
    {

    }*/
}

void WindowsApplication::onKeyPressed(const platform::KeyboardEvent &ev)
{
    if (ev.keycode() == platform::KEY_NONE)
        std::cerr << "Key none!\n";

    std::cerr << "Getted keycode: " << std::hex << ev.keycode() << std::dec << "\n";
}

void WindowsApplication::onKeyReleased(const platform::KeyboardEvent &ev)
{
}

void WindowsApplication::onResize(int w, int h)
{
    // windows related resize things

    m_clientController->resize(w, h);
}

int WindowsApplication::run()
{
    MSG msg;
    int retVal = 0;

    while (true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
        {
            if (!GetMessage(&msg, NULL, 0, 0))
                return msg.wParam;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            retVal = BaseApp::run();
            if (retVal)
                return retVal;
        }
    }
}
