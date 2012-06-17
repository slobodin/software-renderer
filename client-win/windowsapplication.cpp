#include "windowsapplication.h"

#include "windowsviewport.h"
#include <windows.h>

LRESULT WINAPI WindowsApplication::handleMessage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static MouseEvent mouseEvent;

    switch (msg)
    {
    case WM_KEYDOWN:
//        keyboard.keyCode = (IO::EKeyboardCodes)wp;
        //HandleKeyDown(wp);
        return 0;

    case WM_KEYUP:
//        memset(&keyboard, 0, sizeof(keyboard));
        //HandleKeyUp(wp);
        return 0;

    case WM_MOUSEMOVE:
        memset(&mouseEvent, 0, sizeof(MouseEvent));
        mouseEvent.x = LOWORD(lp);
        mouseEvent.y = HIWORD(lp);
        mouseEvent.buttonsState = wp & (MK_LBUTTON | MK_RBUTTON);
        if (wp & MK_MBUTTON)
            mouseEvent.buttonsState |= MouseEvent::MIDDLE_PRESSED;

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

WindowsApplication::WindowsApplication(const char **argv)
    : platform::BaseApp()
{
    m_hInstance = GetModuleHandle(NULL);

    m_clientController = boost::make_shared<base::Controller>(argv);
    m_playerCamera = m_clientController->getCamera();

    m_clientController->setViewport(boost::make_shared<WindowsViewport>(this, 640, 480, m_playerCamera));
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

void WindowsApplication::onMouseEvent(const MouseEvent &ev)
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

void WindowsApplication::onKeyPressed(int keycode)
{
}

void WindowsApplication::onKeyReleased(int keycode)
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
