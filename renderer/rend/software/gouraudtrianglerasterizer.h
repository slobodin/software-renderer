/*
 * gouraudtrianglerasterizer.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef GOURAUDTRIANGLERASTERIZER_H
#define GOURAUDTRIANGLERASTERIZER_H

#include "comm_pch.h"
#include "trianglerasterizer.h"

namespace rend
{

//! Draws gouraud shaded triangle (without perspective correctness)
/**
  *
  */
class GouraudTriangleRasterizer : public TriangleRasterizer
{
public:
    GouraudTriangleRasterizer() { }

    void drawTriangle(const math::Triangle &t, FrameBuffer *fb);
};

}

#endif // GOURAUDTRIANGLERASTERIZER_H
