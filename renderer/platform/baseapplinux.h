/*
 * baseapplinux.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef BASEAPPLINUX_H
#define BASEAPPLINUX_H

// DEPRECATED
#if 0
#ifdef LINUX_VERSION

#include "comm_pch.h"

#include "baseapp.h"
#include "viewport.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

namespace platform
{

DECLARE_EXCEPTION(XServerException)
class XViewport;

class BaseAppLinux : public BaseApp
{
protected:
    sptr(XViewport) m_viewport;

public:
    BaseAppLinux(int argc, const char *argv[]);
    ~BaseAppLinux();

    virtual void onResize(int w, int h);

    virtual int run();
};

class XViewport : public rend::Viewport
{
    Display       * m_display;
    Window          m_window;
    XVisualInfo   * m_visual;
    XImage        * m_XScreenBuffer;

    virtual void resize(int w, int h);

public:
    XViewport(int width, int height, boost::shared_ptr<rend::Camera> camera);
    virtual ~XViewport();

    Display *getXDisplay() { return m_display; }
    Window  &getWindow() { return m_window; }

    void flush(const unsigned char * const pixels);
};

}

#endif
#endif

#endif // BASEAPPLINUX_H
