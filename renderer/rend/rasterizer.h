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

    void makeCCWTriangle(math::vertex &p1, math::vertex &p2, math::vertex &p3);

    //! This functions draw triangle with color
    void drawFillTriangle(math::vertex &p1, math::vertex &p2, math::vertex &p3);
    void drawFillTriangle(const math::Triangle &tr);

    //! This functions draw wireframe triangle
    void drawTriangle(const math::vertex &p1, const math::vertex &p2, const math::vertex &p3);
    void drawTriangle(const math::Triangle &tr);

    //! This functions draw triangle with gouraud shading
    void drawGouraudTriangle(math::vertex &v0, math::vertex &v1, math::vertex &v2);
    void drawGouraudTriangle(const math::Triangle &tr);

    //! This function draws triangle with affine texture mapping
    void drawTexturedTriangle(const math::Triangle &tr);

    //! Helpers for drawing filled triangle
    void drawBottomTriangle(int x1, int y1, int x2, int y2, int x3, int y3, const Color3 &color);
    void drawTopTriangle(int x1, int y1, int x2, int y2, int x3, int y3, const Color3 &color);
    void rasterizeTopOrBottomTriangle(int x1, int y1, int x2, int x3, int y3,
                                      double dxLeft, double dxRight, double xs, double xe, const Color3 &color);

    //! This functions draw lines
    bool clipLine(math::vec3 &p1, math::vec3 &p2);
    void drawLine(const math::vertex &p1, const math::vertex &p2);

public:
    Rasterizer(const int width, const int height);

    virtual void render(const RenderList &rendlist);

    virtual void beginFrame(sptr(Viewport) viewport);
    virtual void endFrame(sptr(Viewport) viewport);

    virtual void resize(int w, int h);
};

}

#endif // RASTERIZER_H
