/*
 * baseapplinux.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "baseapplinux.h"

#ifdef LINUX_VERSION

#include "camera.h"
#include "controller.h"
#include "events.h"

#include <cstdlib>
#include <cstdint>

namespace platform
{

BaseAppLinux::BaseAppLinux(int argc, const char *argv[])
    : BaseApp()
{
    m_clientController = boost::make_shared<base::Controller>(argc, argv);

    m_clientController->createViewport<XViewport>();
    m_viewport = boost::dynamic_pointer_cast<XViewport>(m_clientController->getViewport());
}

BaseAppLinux::~BaseAppLinux()
{
}

void BaseAppLinux::onResize(int w, int h)
{
    m_clientController->resize(w, h);
}

int BaseAppLinux::run()
{
    XEvent report;

    while (1)
    {
        BaseApp::run();

        XNextEvent(m_viewport->getXDisplay(), &report);

        switch (report.type)
        {
        case Expose:
            break;

        case ConfigureNotify:
            if ((report.xconfigure.width != m_viewport->getWidth()) ||
                (report.xconfigure.height != m_viewport->getHeight()))
            {
                onResize(report.xconfigure.width, report.xconfigure.height);
            }
            break;

        case MotionNotify:
        {
            platform::MouseEvent mouseEvent;

            mouseEvent.x = report.xbutton.x;
            mouseEvent.y = report.xbutton.y;

            mouseEvent.buttonsState = (report.xbutton.state & Button1Mask)
                    ? platform::MouseEvent::LEFT_PRESSED : 0;
            mouseEvent.buttonsState |= (report.xbutton.state & Button3Mask)
                    ? platform::MouseEvent::RIGHT_PRESSED : 0;
            mouseEvent.buttonsState |= (report.xbutton.state & Button2Mask)
                    ? platform::MouseEvent::MIDDLE_PRESSED : 0;

            onMouseEvent(mouseEvent);
        }
            break;

        case ButtonRelease:
        case ButtonPress:
        {
            platform::MouseEvent mouseEvent;

            mouseEvent.x = report.xbutton.x;
            mouseEvent.y = report.xbutton.y;
            mouseEvent.buttonsState = (report.xbutton.state & Button1Mask)
                    ? platform::MouseEvent::LEFT_PRESSED : 0;
            mouseEvent.buttonsState |= (report.xbutton.state & Button3Mask)
                    ? platform::MouseEvent::RIGHT_PRESSED : 0;
            mouseEvent.buttonsState |= (report.xbutton.state & Button2Mask)
                    ? platform::MouseEvent::MIDDLE_PRESSED : 0;

            switch(report.xbutton.button)
            {
            case Button1:
                mouseEvent.buttonsState ^= platform::MouseEvent::LEFT_PRESSED;
                break;

            case Button3:
                mouseEvent.buttonsState ^= platform::MouseEvent::RIGHT_PRESSED;
                break;

            case Button2:
                mouseEvent.buttonsState ^= platform::MouseEvent::MIDDLE_PRESSED;
                break;
            }

            onMouseEvent(mouseEvent);
        }
            break;

        case KeyPress:
        {
            static char keyStr[20];
            static KeySym keySym;

            XLookupString(&report.xkey, keyStr, sizeof(keyStr), &keySym, 0);

            platform::KeyboardEvent kbEvent(keySym);

            onKeyPressed(kbEvent);
        }
            break;

        case KeyRelease:
        {
            static char keyStr[20];
            static KeySym keySym;

            XLookupString(&report.xkey, keyStr, sizeof(keyStr), &keySym, 0);

            platform::KeyboardEvent kbEvent(keySym);

            onKeyReleased(kbEvent);
        }
            break;

        default:
            break;
        }
    }

    return 0;
}

void XViewport::resize(int w, int h)
{
    Viewport::resize(w, h);

    if (m_XScreenBuffer)
    {
        XDestroyImage(m_XScreenBuffer);

        m_XScreenBuffer = XCreateImage(m_display,
                                       m_visual->visual, m_visual->depth,
                                       ZPixmap, 0, 0, w, h,
                                       BitmapPad(m_display), 0);

        if (m_XScreenBuffer)
            m_XScreenBuffer->data = (char*) malloc(m_XScreenBuffer->bytes_per_line *
                                                   m_XScreenBuffer->height *
                                                   sizeof(char));
    }
}

XViewport::XViewport(int width, int height, boost::shared_ptr<rend::Camera> camera)
    : Viewport(width, height, camera),
      m_display(0), m_window(0), m_visual(0), m_XScreenBuffer(0)
{
    m_display = XOpenDisplay(getenv("DISPLAY"));
    if (!m_display)
        throw XServerException("Can't connect to X Server");

    int screenNumber = DefaultScreen(m_display);

    // create visual
    XVisualInfo visTempl;
    int visNumber;

    visTempl.screen = screenNumber;
    visTempl.depth = 24;
    m_visual = XGetVisualInfo(m_display, VisualScreenMask | VisualDepthMask, &visTempl, &visNumber);

    if (!m_visual)
    {
        XCloseDisplay(m_display);
        m_display = 0;
        throw XServerException("Can't recieve visual info");
    }

    // create colormap
    Colormap colormap = XCreateColormap(m_display, RootWindow(m_display, m_visual->screen),
                                        m_visual->visual, AllocNone);

    XSetWindowAttributes attrib;
    memset(&attrib, 0, sizeof(XSetWindowAttributes));

    attrib.colormap = colormap;
    attrib.event_mask = StructureNotifyMask | FocusChangeMask | ExposureMask;
    attrib.event_mask |= PointerMotionMask | ButtonPressMask | KeyPressMask |
            ButtonReleaseMask | KeyReleaseMask | ButtonMotionMask;

    m_window = XCreateWindow(m_display, RootWindow(m_display, m_visual->screen), 0, 0, m_width, m_height,
                             0, m_visual->depth, InputOutput, m_visual->visual,
                             CWBorderPixel | CWColormap | CWEventMask | CWOverrideRedirect,
                             &attrib);

    if (!m_window)
    {
        XCloseDisplay(m_display);
        m_display = 0;
        throw XServerException("Can't create X window");
    }

    XMapRaised(m_display, m_window);

    m_XScreenBuffer = XCreateImage(m_display, m_visual->visual, m_visual->depth,
                                   ZPixmap, 0, 0, m_width, m_height,
                                   BitmapPad(m_display), 0);
    if (m_XScreenBuffer)
        m_XScreenBuffer->data = (char *)malloc(m_XScreenBuffer->bytes_per_line *
                                               m_XScreenBuffer->height *
                                               sizeof(char));
    else
        syslog << "Can't create X screen buffer" << logerr;
}

XViewport::~XViewport()
{
    if (m_XScreenBuffer)
        XDestroyImage(m_XScreenBuffer);

    // hide window
    if (m_display && m_window)
    {
        XUnmapWindow(m_display, m_window);
        XFlush(m_display);

        // destroy window
        XDestroyWindow(m_display, m_window);
    }

    // end session
    if (m_display)
        XCloseDisplay(m_display);

    if (m_visual)
        XFree(m_visual);
}

// TODO: this func is very slooow
void XViewport::flush(const unsigned char *const pixels)
{
    if (!m_XScreenBuffer)
    {
        syslog << "X screen buffer not initialized" << logerr;
        return;
    }

    if (m_XScreenBuffer->bits_per_pixel != 32)
    {
        syslog << "Unsupported image depth" << logerr;
        return;
    }

    if ((m_width != m_XScreenBuffer->width) || (m_height != m_XScreenBuffer->height))
    {
        syslog << "Source and destination images are not equal\n" << logerr;
        return;
    }

    unsigned char *destData = reinterpret_cast<unsigned char *>(m_XScreenBuffer->data);
    const unsigned char* srcData = pixels;

    int destPitch = m_XScreenBuffer->bytes_per_line;
    int srcPitch = 3 * m_width;

    for (int line = 0; line < m_height; line++)
    {
        const unsigned char *sB = srcData;
        uint32_t *dB = (uint32_t *)destData;

        for (int x = 0; x < m_width; ++x)
        {
            *dB = 0xff000000 | (sB[0] << 16) | (sB[1] << 8) | sB[2];

            sB += 3;
            dB++;
        }

        destData += destPitch;
        srcData += srcPitch;
    }

    GC gc = DefaultGC(m_display, DefaultScreen(m_display));

    XPutImage(m_display, m_window, gc, m_XScreenBuffer, 0, 0, 0, 0, m_width, m_height);
}

}

#endif
