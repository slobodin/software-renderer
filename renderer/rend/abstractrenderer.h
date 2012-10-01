/*
 * abstractrenderer.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef ABSTRACTRENDERER_H
#define ABSTRACTRENDERER_H

#include "comm_pch.h"

namespace rend
{

DECLARE_EXCEPTION(RendererException)

class Viewport;
class RenderList;

//! Rendering interface.
/**
  *
  */
class AbstractRenderer
{

public:
    AbstractRenderer() { }
    virtual ~AbstractRenderer() { }

    virtual void render(const RenderList &rendlist) = 0;

    virtual void beginFrame(sptr(Viewport) viewport) = 0;
    virtual void endFrame(sptr(Viewport) viewport) = 0;

    virtual void resize(int w, int h) = 0;
};

}

#endif // ABSTRACTRENDERER_H
