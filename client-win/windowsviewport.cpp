#include "windowsviewport.h"
#include "windowsapplication.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    if (msg == WM_CREATE)
    {
        LPCREATESTRUCT cs = (LPCREATESTRUCT)lp;
        WindowsApplication *param = (WindowsApplication*)cs->lpCreateParams;
        SetWindowLong(hwnd, GWL_USERDATA, (long)param);
    }
    else
    {
        if (msg == WM_DESTROY)
        {

        }

        WindowsApplication* app = (WindowsApplication*)GetWindowLong(hwnd, GWL_USERDATA);
        if (app)
            return app->handleMessage(hwnd, msg, wp, lp);
    }

    return DefWindowProc(hwnd, msg, wp, lp);
}

WindowsViewport::WindowsViewport(WindowsApplication *app,
                                 int width, int height,
                                 boost::shared_ptr<rend::Camera> camera)
    : Viewport(width, height, camera)
{
    const wchar_t *className = L"wc.MainWindow";

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
    wcex.hInstance = app->getAppInstance();
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
                            0, 0, app->getAppInstance(), app);

    if (!m_hWnd)
    {
        UnregisterClass(className, app->getAppInstance());
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

void WindowsViewport::frameBegin()
{
}

void WindowsViewport::flush(unsigned char *pixels)
{
}
