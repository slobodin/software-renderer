/*
 * xviewport.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef XVIEWPORT_H
#define XVIEWPORT_H

#include "renderer.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>

DECLARE_EXCEPTION(XServerException)

class XViewport : public rend::Viewport
{
    Display *m_display;
    Window m_window;
    XVisualInfo *m_visual;
    XImage *m_XScreenBuffer;

public:
    XViewport(int width, int height, boost::shared_ptr<rend::Camera> camera);
    virtual ~XViewport();

    Display *getXDisplay() { return m_display; }

    void frameBegin();
    void flush(const unsigned char * const pixels);
};

#endif // XVIEWPORT_H
