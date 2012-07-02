/*
 * xviewport.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "xviewport.h"
#include <cstdlib>
#include <cstdint>

static const int DEFAULT_EVENT_MASK =
        ExposureMask |          // redraw window
        ButtonPressMask |       // button was pressed
        ButtonReleaseMask |     // button was released
        EnterWindowMask |       // entering in the window
        LeaveWindowMask |       // leaving window
        PointerMotionMask |     // trace cursor position
        ButtonMotionMask |      // trace cursor position when a button pressed
//        ResizeRedirectMask |    // resize event
        KeyPressMask |          // key pressed
        KeyReleaseMask;         // key released

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
    Colormap colormap = XCreateColormap(m_display, RootWindow(m_display, m_visual->screen), m_visual->visual, AllocNone);

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
        m_XScreenBuffer->data = (char *)malloc(m_XScreenBuffer->bytes_per_line * m_XScreenBuffer->height * sizeof(char));
    else
        std::cerr << "Can't create X screen buffer\n";

//    XSelectInput(d, m_window, DEFAULT_EVENT_MASK);
//    XMapWindow(d, m_window);
//    XFlush(d);
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

void XViewport::frameBegin()
{
}

void XViewport::flush(const unsigned char *const pixels)
{
    if (!m_XScreenBuffer)
        return;

    if (m_XScreenBuffer->bits_per_pixel != 32)
    {
        std::cerr << "Unsupported image depth\n";
        return;
    }

    if ((m_width != m_XScreenBuffer->width) || (m_height != m_XScreenBuffer->height))
    {
        std::cerr << "Source and destination images are not equal\n";
        return;
    }

    unsigned char *destData = reinterpret_cast<unsigned char *>(m_XScreenBuffer->data);
    const unsigned char* srcData = pixels;

    int destPitch = m_XScreenBuffer->bytes_per_line;
    int srcPitch = 24 * m_width;

    for (int line = 0; line < m_height; line++)
    {
        const unsigned char *sB = srcData;
        uint32_t *dB = (uint32_t *)destData;

        for (int x = 0; x < m_width; ++x)
        {
            *dB = 0xff000000 | (sB[0] << 16) | (sB[1] << 8) | sB[2];

            sB += 3;
            ++dB;
        }

        destData += destPitch;
        srcData += srcPitch;
    }

    GC gc = DefaultGC(m_display, DefaultScreen(m_display));

    XPutImage(m_display, m_window, gc, m_XScreenBuffer, 0, 0, 0, 0, m_width, m_height);
}
