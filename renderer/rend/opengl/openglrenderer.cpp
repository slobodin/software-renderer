/*
 * openglrenderer.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "openglrenderer.h"
#include "platform/baseapptk.h"
#include "viewport.h"
#include "renderlist.h"
#include "guiobject.h"
#include "m44.h"

#ifdef __linux__
#include <tcl8.5/tk.h>
#include <tcl8.5/tcl.h>
#include <GL/gl.h>
#include <GL/glx.h>
#elif WIN32
#include <tcl8.5/tk.h>
#include <tcl8.5/tcl.h>
#endif
#include <cpptk-1.0.2/cpptk.h>
#include <cpptk-1.0.2/base/cpptkbase.h>

namespace rend
{

OpenGLRenderer::OpenGLRenderer(const shared_ptr<Viewport> viewport)
{
#ifdef __linux__
    auto tkViewport = boost::dynamic_pointer_cast<platform::TkViewport>(viewport);

    if (!tkViewport)
        throw RendererException("Only tk widgets supported");       // x11 and win32 deprecated

//    Display *display = XOpenDisplay(getenv("DISPLAY"));

//    string windowId = Tk::winfo(Tk::id, ".");
//    stringstream ss(windowId);
//    ss >> std::hex >> m_xWindowId;
////    m_xWindowId = windowId;

//    XWindowAttributes wndAttrib;
//    XGetWindowAttributes(display, m_xWindowId, &wndAttrib);



















//    string scrStr = Tk::winfo(Tk::screen, ".c");


//    Display *d = XOpenDisplay(scrStr.c_str());
//    Tk_Window tkwin = Tk_IdToWindow(d, m_xWindowId);

////    Visual *vi = Tk_Visual(tkwin);

//    Tk_Window mainwin = Tk_MainWindow(Tk::getInterp());



////    /* fill in flags normally passed in that affect behavior */
////    (void) glXGetConfig(dpy, visinfo, GLX_RGBA, &togl->RgbaFlag);
////    (void) glXGetConfig(dpy, visinfo, GLX_DOUBLEBUFFER,
////            &togl->DoubleFlag);
////    (void) glXGetConfig(dpy, visinfo, GLX_STEREO, &togl->StereoFlag);









//    // displayName.screenIndex.
////    string scr = Tk::winfo(Tk::screen, ".c");

////             // FIXME: need to get display from Window, how??
////    int screen = DefaultScreen(d);

////    XVisualInfo *vi = glXChooseVisual(d, screen, attrListDbl);
////    if (vi == NULL)
////        throw RendererException("Can't create context.");

//    XVisualInfo templ;
//    int     count = 1;

//    templ.visualid = (int)Tk::winfo(Tk::visualid, ".c");
//    XVisualInfo *vi = XGetVisualInfo(d, VisualIDMask, &templ, &count);
//    if (vi == NULL) {
//            throw RendererException("Only tk widgets supported");
//    }

//    GLXContext context = glXGetCurrentContext();// glXCreateContext(d, vi, 0, GL_TRUE);
//    glXMakeCurrent(d, m_xWindowId, context);

//    int a;
//    a = 4;

////    (void) glXMakeCurrent(togl->display,
////            togl->TkWin ? Tk_WindowId(togl->TkWin) : None, togl->GlCtx);
////    Tcl_Interp *interp = Tk::getInterp();
////    if (Togl_Init(interp) == TCL_ERROR)
////    {
////        syslog << "Can't init Togl" << logerr;
////        throw RendererException("Uninitialized");
////    }

////    Togl_DisplayFunc(OpenGLRenderer::ondisplay);
////    Togl_ReshapeFunc(OpenGLRenderer::onreshape);


//    Tk_IdToWindow(Display *display, Window window);
#endif
}

void OpenGLRenderer::onreshape(Togl *togl)
{
}

void OpenGLRenderer::ondisplay(Togl *togl)
{
}

OpenGLRenderer::~OpenGLRenderer()
{
}

void OpenGLRenderer::renderWorld(const RenderList &rendlist)
{
}

void OpenGLRenderer::renderGui(const list<sptr(GuiObject)> &guiObjects)
{
}

void OpenGLRenderer::beginFrame(sptr(Viewport) viewport)
{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
//    float m[16];

//    math::Vector3D pos(_camera.GetPosition());

//    _camera.GetCameraLookAtMatrix(m);

//    glViewport(0, 0, _camera.GetWidth(), _camera.GetHeight());
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(_camera.GetFovy(), _camera.GetAspectRatio(), _camera.GetZNear(), _camera.GetZFar());

//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glMultMatrixf(m);
//    glTranslatef(-pos.x, -pos.y, -pos.z);
}

void OpenGLRenderer::endFrame(sptr(Viewport) viewport)
{
//    glXSwapBuffers(display, m_renderingWindowId);
//    glXSwapBuffers(Tk_Display(togl->TkWin), Tk_WindowId(togl->TkWin));
}

void OpenGLRenderer::resize(int w, int h)
{
//    glViewport(0, 0, w, h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
    //	gluPerspective(camera->GetFovy(), camera->GetAspectRatio(), camera->GetZNear(), camera->GetZFar());
}

void OpenGLRenderer::setWorldViewMatrix(const math::M44 &m)
{
}

void OpenGLRenderer::setProjectionMatrix(const math::M44 &m)
{
}

}

