/*
 * baseappwin.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "stdafx.h"

#include "baseappwin.h"

#include "controller.h"
#include "camera.h"
#include "events.h"

namespace platform
{

LRESULT WINAPI BaseAppWin::handleMessage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
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
        onResize(LOWORD(lp), HIWORD(lp));
        return 0;

    default:
        return DefWindowProc(hwnd, msg, wp, lp);
    }
}

BaseAppWin::BaseAppWin(int argc, const char **argv)
{
    m_clientController = std::make_shared<base::Controller>(argc, argv);

    m_clientController->createViewport<WindowsViewport>();
}
BaseAppWin::~BaseAppWin()
{

}

void BaseAppWin::onResize(int w, int h)
{
    m_clientController->resize(w, h);
}

int BaseAppWin::run()
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

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    if (msg == WM_CREATE)
    {
        LPCREATESTRUCT cs = (LPCREATESTRUCT)lp;
        BaseAppWin *param = (BaseAppWin*)cs->lpCreateParams;
        SetWindowLong(hwnd, GWL_USERDATA, (long)param);
    }
    else
    {
        if (msg == WM_DESTROY)
        {

        }

        BaseAppWin* app = (BaseAppWin*)GetWindowLong(hwnd, GWL_USERDATA);
        if (app)
            return app->handleMessage(hwnd, msg, wp, lp);
    }

    return DefWindowProc(hwnd, msg, wp, lp);
}

WindowsViewport::WindowsViewport(int width, int height, sptr(rend::Camera) camera)
    : Viewport(width, height, camera)
{
    const TCHAR *className = TEXT("wc.MainWindow");

    WNDCLASSEX wcex;
    memset(&wcex, 0, sizeof(WNDCLASSEX));

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = 0;
    wcex.lpszClassName = className;
    wcex.hIcon = 0;
    wcex.hIconSm = 0;
    wcex.hCursor = (HCURSOR)LoadCursor(0, IDC_ARROW);
    wcex.hInstance = GetModuleHandle(0);//app->getAppInstance();
    wcex.lpfnWndProc = (WNDPROC)WndProc;

    if (!RegisterClassEx(&wcex))
        throw WindowsException("Can't register window class");

    RECT viewportRect;
    viewportRect.left = 0;
    viewportRect.top = 0;
    viewportRect.right = width;
    viewportRect.bottom = height;

    AdjustWindowRect(&viewportRect, WS_POPUPWINDOW | WS_CAPTION | WS_MINIMIZEBOX, false);

    HDC desktopDC = GetDC(GetDesktopWindow());
    int screenWidth = GetDeviceCaps(desktopDC, HORZRES);
    int screenHeight = GetDeviceCaps(desktopDC, VERTRES);
    ReleaseDC(GetDesktopWindow(), desktopDC);

    m_hWnd = CreateWindowEx(0, className, L"Main window", WS_POPUPWINDOW | WS_CAPTION | WS_MINIMIZEBOX,
        screenWidth / 2 - width / 2, screenHeight / 2 - height / 2,
        viewportRect.right - viewportRect.left + 1,
        viewportRect.bottom - viewportRect.top + 1,
        0, 0, GetModuleHandle(0), BaseApp::instance());

    if (!m_hWnd)
    {
        UnregisterClass(className, GetModuleHandle(0));
        throw WindowsException("Failed to create a window");
    }


    m_hDC = GetDC(m_hWnd);
    if (!m_hDC)
        throw WindowsException("Failed to create device context");

    ShowWindow(m_hWnd, SW_SHOW);
}

WindowsViewport::~WindowsViewport()
{
    if (m_hDC)
        ReleaseDC(m_hWnd, m_hDC);

    if (m_hWnd)
        DestroyWindow(m_hWnd);
}

void WindowsViewport::flush(const unsigned char *const pixels)
{
    if (!m_hDC)
        return;

    static BITMAPINFO bmi;
    memset(&bmi, 0, sizeof(bmi));

    bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth       = m_width;
    bmi.bmiHeader.biHeight      = -m_height;
    bmi.bmiHeader.biPlanes      = 1;
    bmi.bmiHeader.biBitCount    = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage   = 0;

    SetDIBitsToDevice(m_hDC,
        0, 0,
        m_width, m_height,
        0, 0,
        0, m_height,
        pixels,
        &bmi,
        DIB_RGB_COLORS);
}

}