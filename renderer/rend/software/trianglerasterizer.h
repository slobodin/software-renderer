/*
 * trianglerasterizer.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef TRIANGLERASTERIZER_H
#define TRIANGLERASTERIZER_H

#include "comm_pch.h"

namespace math
{

struct vertex;
class Triangle;

}

namespace rend
{

class FrameBuffer;

//! Abstract triangle rasterizer.
/**
  * There are maybe flat, gouraud, wireframe, textured triangle rasterizers and the list goes on.
  */
class TriangleRasterizer
{
protected:
    void makeCCWTriangle(math::vertex &p1, math::vertex &p2, math::vertex &p3);

public:
    TriangleRasterizer() { }
    virtual ~TriangleRasterizer() { }

    //! Draws given triangle into framebuffer.
    virtual void drawTriangle(const math::Triangle &t, FrameBuffer *fb) = 0;
};

}

#endif // TRIANGLERASTERIZER_H
