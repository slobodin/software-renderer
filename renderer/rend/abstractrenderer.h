/*
 * abstractrenderer.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef ABSTRACTRENDERER_H
#define ABSTRACTRENDERER_H

#include "comm_pch.h"

namespace math
{

struct M44;

}

namespace rend
{

DECLARE_EXCEPTION(RendererException)

class Viewport;
class RenderList;
class GuiObject;

//! Rendering interface.
/**
  *
  */
class AbstractRenderer
{

public:
    AbstractRenderer() { }
    virtual ~AbstractRenderer() { }

    virtual void renderWorld(const RenderList *rendlist) = 0;
    virtual void renderGui(const list<sptr(GuiObject)> &guiObjects) = 0;

    virtual void beginFrame(sptr(Viewport) viewport) = 0;
    virtual void endFrame(sptr(Viewport) viewport) = 0;

    virtual void resize(int w, int h) = 0;

    virtual void setWorldViewMatrix(const math::M44 &m) = 0;
    virtual void setProjectionMatrix(const math::M44 &m) = 0;
};

}

#endif // ABSTRACTRENDERER_H
