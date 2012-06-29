/*
 * rasterizer.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "comm_pch.h"

#include "mesh.h"
#include "camera.h"
#include "color.h"
#include "framebuffer.h"
#include "material.h"
#include "poly.h"
#include "renderlist.h"
#include "vertex.h"

namespace rend
{

class Viewport;

class Rasterizer
{
    FrameBuffer m_fb;

    void drawFillTriangle(const math::vertex &p1, const math::vertex &p2, const math::vertex &p3);
    void drawFillTriangle(const math::Triangle &tr);

    void drawTriangle(const math::vertex &p1, const math::vertex &p2, const math::vertex &p3);
    void drawTriangle(const math::Triangle &tr);

    void drawGouraudTriangle(const math::vertex &v1, const math::vertex &v2, const math::vertex &v3);
    void drawGouraudTriangle(const math::Triangle &tr);

    void drawBottomTriangle(int x1, int y1, int x2, int y2, int x3, int y3, const Color3 &color);
    void drawTopTriangle(int x1, int y1, int x2, int y2, int x3, int y3, const Color3 &color);

    bool clipLine(math::vec3 &p1, math::vec3 &p2);
    void drawLine(const math::vertex &p1, const math::vertex &p2);

public:
    Rasterizer(const int width, const int height);

    void rasterize(const RenderList &rendlist);

    void beginFrame(sptr(Viewport) viewport);
    void endFrame(sptr(Viewport) viewport);

    void resize(int w, int h);
};

}

#endif // RASTERIZER_H
