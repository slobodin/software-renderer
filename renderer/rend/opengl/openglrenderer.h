/*
 * openglrenderer.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "comm_pch.h"
#include "abstractrenderer.h"

#ifdef __linux__
#include <X11/Xlib.h>
#endif

struct Togl;

namespace rend
{

class RenderList;
class Viewport;

class OpenGLRenderer : public AbstractRenderer
{
    static void onreshape(Togl *togl);
    static void ondisplay(Togl *togl);

#ifdef __linux
    Window m_xWindowId;
#endif

public:
    OpenGLRenderer(const shared_ptr<Viewport> viewport);
    ~OpenGLRenderer();

    virtual void renderWorld(const RenderList &rendlist);
    virtual void renderGui(const list<sptr(GuiObject)> &guiObjects);

    virtual void beginFrame(sptr(Viewport) viewport);
    virtual void endFrame(sptr(Viewport) viewport);

    virtual void resize(int w, int h);

    virtual void setWorldViewMatrix(const math::M44 &m);
    virtual void setProjectionMatrix(const math::M44 &m);
};

}

#endif // OPENGLRENDERER_H
