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

DECLARE_EXCEPTION(XServerException)

class XViewport : public rend::Viewport
{
    Display *d;
    Window m_window;

public:
    XViewport(int width, int height, boost::shared_ptr<rend::Camera> camera);
    virtual ~XViewport();

    Display *getXDisplay() { return d; }

    void frameBegin();
    void flush(unsigned char *pixels);
};

#endif // XVIEWPORT_H
