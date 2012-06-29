/*
 * xviewport.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "xviewport.h"
#include <cstdlib>

XViewport::XViewport(int width, int height, boost::shared_ptr<rend::Camera> camera)
    : Viewport(width, height, camera),
      d(0), m_window(0)
{
    d = XOpenDisplay(/*getenv("DISPLAY")*/"");
    if (!d)
        throw XServerException("Can't connect to X Server");

    m_window = XCreateSimpleWindow(d, RootWindow(d, 0), 0, 0, width, height, 0,
                                   WhitePixel(d, 0), WhitePixel(d, 0));

    if (!m_window)
        throw XServerException("Can't create X window");
}

XViewport::~XViewport()
{
    // hide window
    if (d && m_window)
    {
        XUnmapWindow(d, m_window);
        XFlush(d);

        // destroy window
        XDestroyWindow(d, m_window);
    }

    // end session
    if (d)
        XCloseDisplay(d);
}

void XViewport::flush(unsigned char *pixels)
{
}
