/*
 * flattrianglerasterizer.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef FLATTRIANGLERASTERIZER_H
#define FLATTRIANGLERASTERIZER_H

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
public:
    FlatTriangleRasterizer() { }

    void drawTriangle(const math::Triangle &t, FrameBuffer *fb);
};

}

#endif // FLATTRIANGLERASTERIZER_H
