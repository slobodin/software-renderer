/*
 * flattrianglerasterizer.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef FLATTRIANGLERASTERIZER_H
#define FLATTRIANGLERASTERIZER_H

#include "comm_pch.h"
#include "trianglerasterizer.h"

namespace rend
{

class Color3;

//! Draws triangle with plane color.
/**
  *
  */
class FlatTriangleRasterizer : public TriangleRasterizer
{
    //! Helpers for drawing filled triangle.
    void drawBottomTriangle(int x1, int y1, int x2, int y2, int x3, int y3,
                            const Color3 &color, FrameBuffer *fb);
    void drawTopTriangle(int x1, int y1, int x2, int y2, int x3, int y3,
                         const Color3 &color, FrameBuffer *fb);
    void rasterizeTopOrBottomTriangle(int x1, int y1, int x2, int x3, int y3,
                                      double dxLeft, double dxRight, double xs, double xe,
                                      const rend::Color3 &color, FrameBuffer *fb);
public:
    FlatTriangleRasterizer() { }

    void drawTriangle(const math::Triangle &t, FrameBuffer *fb);
};

}

#endif // FLATTRIANGLERASTERIZER_H
