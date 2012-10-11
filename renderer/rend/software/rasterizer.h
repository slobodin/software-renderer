/*
 * rasterizer.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "comm_pch.h"

#include "abstractrenderer.h"
#include "framebuffer.h"

namespace math
{

struct vertex;
class Triangle;

}

namespace rend
{

class RenderList;
class Viewport;

class Viewport;

//! Performs triangle rasterization.
/**
  * Supports line, triangle with color, gouraud and texture rasterization (without perspective correction).
  */
class Rasterizer : public AbstractRenderer
{
    FrameBuffer m_fb;

    //! This functions draw triangle with gouraud shading
    void drawGouraudTriangle(math::vertex &v0, math::vertex &v1, math::vertex &v2);
    void drawGouraudTriangle(const math::Triangle &tr);

    //! This function draws triangle with affine texture mapping
    void drawTexturedTriangle(const math::Triangle &tr);

public:
    Rasterizer(int width, int height);

    virtual void render(const RenderList &rendlist);

    virtual void beginFrame(sptr(Viewport) viewport);
    virtual void endFrame(sptr(Viewport) viewport);

    virtual void resize(int w, int h);
};

}

#endif // RASTERIZER_H
