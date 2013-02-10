/*
 * texturedtrianglerasterizer.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef TEXTUREDTRIANGLERASTERIZER_H
#define TEXTUREDTRIANGLERASTERIZER_H

#include "trianglerasterizer.h"

namespace rend
{

//! Draws textured triangle (without perspective correctness).
/**
  *
  */
class TexturedTriangleRasterizer : public TriangleRasterizer
{
public:
    TexturedTriangleRasterizer() { }

    void drawTriangle(const math::Triangle &t, FrameBuffer *fb);
};

}

#endif // TEXTUREDTRIANGLERASTERIZER_H
