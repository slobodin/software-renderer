/*
 * baseapptk.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "baseapptk.h"

#include "camera.h"
#include "controller.h"

#include <tcl/tk.h>
#include <tcl/tcl.h>
#include <cpptk-1.0.2/cpptk.h>
#include <cpptk-1.0.2/base/cpptkbase.h>

namespace platform
{

using namespace Tk;

BaseAppTk *BaseAppTk::m_instance = 0;

void BaseAppTk::tkUpdate()
{
    m_instance->BaseApp::run();     // run the frame

    Tk::afteridle(m_instance->m_updateCallback);
}

void BaseAppTk::tkMouseMotion(int x, int y)
{
    int dx = m_instance->mouseEvPrev.x - x;
    int dy = m_instance->mouseEvPrev.y - y;

    m_instance->onMouseEvent(MouseEvent(dx, dy, MouseEvent::LEFT_PRESSED));

    m_instance->mouseEvPrev.x = x;
    m_instance->mouseEvPrev.y = y;
}

void BaseAppTk::tkMousePress(int x, int y)
{
    m_instance->mouseEvPrev.x = x;
    m_instance->mouseEvPrev.y = y;

    m_instance->mouseEvPrev.buttonsState |= MouseEvent::LEFT_PRESSED;

//    m_instance->onMouseEvent(m_instance->mouseEv);
}

void BaseAppTk::tkMouseRelease(int x, int y)
{
    m_instance->mouseEvPrev.x = x;
    m_instance->mouseEvPrev.y = y;
    m_instance->mouseEvPrev.buttonsState ^= MouseEvent::LEFT_PRESSED;

    //    m_instance->onMouseEvent(m_instance->mouseEv);
}

void BaseAppTk::tkKeyW()
{
    KeyboardEvent kb(KEY_KEY_W);
    m_instance->onKeyPressed(kb);
}

void BaseAppTk::tkKeyA()
{
    KeyboardEvent kb(KEY_KEY_A);
    m_instance->onKeyPressed(kb);
}

void BaseAppTk::tkKeyS()
{
    KeyboardEvent kb(KEY_KEY_S);
    m_instance->onKeyPressed(kb);
}

void BaseAppTk::tkKeyD()
{
    KeyboardEvent kb(KEY_KEY_D);
    m_instance->onKeyPressed(kb);
}

BaseAppTk::BaseAppTk(int argc, const char *argv[])
    : BaseApp()
{
    m_clientController = boost::make_shared<base::Controller>(argc, argv);

    m_clientController->createViewport<TkViewport>();
    m_viewport = boost::dynamic_pointer_cast<TkViewport>(m_clientController->getViewport());

    Tk::init((char *)argv[0]);

    Tk::wm(Tk::title, ".", "Nyan");

    // create rendering canvas
    Tk::images(Tk::create, Tk::photo, "canvas_photo")
            -Tk::width(m_viewport->getWidth())
            -Tk::height(m_viewport->getHeight());
    Tk::canvas(".c") -Tk::highlightthickness(0)
            -Tk::width(m_viewport->getWidth())
            -Tk::height(m_viewport->getHeight());
    Tk::pack(".c") -Tk::fill(Tk::both) -Tk::expand(true);
    (".c" << Tk::create(Tk::image, 0, 0)) -Tk::image("canvas_photo") -Tk::anchor(nw);

    m_viewport->setFrameName("canvas_photo");

    m_instance = this;      // FIXME: not really singletone

    // setup update event
    m_updateCallback = Tk::callback(&BaseAppTk::tkUpdate);
    Tk::after(500, m_updateCallback);

    // input support...
    Tk::bind(".c", "<B1-Motion>", &BaseAppTk::tkMouseMotion, event_x, event_y);
    Tk::bind(".c", "<ButtonPress-1>", &BaseAppTk::tkMousePress, event_x, event_y);
    Tk::bind(".c", "<ButtonRelease-1>", &BaseAppTk::tkMouseRelease, event_x, event_y);

    Tk::bind(".", "<Key-w>", &BaseAppTk::tkKeyW);    // where is my metaprogramming?
    Tk::bind(".", "<Key-a>", &BaseAppTk::tkKeyA);
    Tk::bind(".", "<Key-s>", &BaseAppTk::tkKeyS);
    Tk::bind(".", "<Key-d>", &BaseAppTk::tkKeyD);
}

BaseAppTk::~BaseAppTk()
{
}

void BaseAppTk::onResize(int w, int h)
{
    m_clientController->resize(w, h);
}

int BaseAppTk::run()
{
    Tk::runEventLoop();

    return 0;
}

void TkViewport::resize(int w, int h)
{
    Viewport::resize(w, h);
}

TkViewport::TkViewport(int width, int height, boost::shared_ptr<rend::Camera> camera)
    : Viewport(width, height, camera)
{
}

TkViewport::~TkViewport()
{
}

void TkViewport::setFrameName(const std::string &name)
{
    m_frameName = name;
}

void TkViewport::flush(const unsigned char *const pixels)
{
    Tk_PhotoHandle fbphoto;
    Tk_PhotoImageBlock block;
    Tcl_Interp *fbinterp = Tk::globalTclInterpret;

    if ((fbphoto = Tk_FindPhoto(fbinterp, m_frameName.c_str())) == NULL)
    {
        std::cerr << "Image creation unsuccessful. Can't find" << m_frameName.c_str() << std::endl;
        return;
    }

    block.pixelPtr = (unsigned char *)pixels;
    block.width = m_width;
    block.height = m_height;
    block.pitch = 4 * m_width;
    block.pixelSize = 4;
    block.offset[0] = 0;
    block.offset[1] = 1;
    block.offset[2] = 2;
    block.offset[3] = 0;

    Tk_PhotoPutBlock(fbinterp, fbphoto, &block, 0, 0, m_width, m_height, TK_PHOTO_COMPOSITE_SET);
}

}
