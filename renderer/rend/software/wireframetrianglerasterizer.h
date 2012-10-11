/*
 * wireframetrianglerasterizer.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef WIREFRAMETRIANGLERASTERIZER_H
#define WIREFRAMETRIANGLERASTERIZER_H

#include "comm_pch.h"
#include "trianglerasterizer.h"

namespace rend
{
//! Draws wireframe triangle.
/**
  *
  */
class WireframeTriangleRasterizer : public TriangleRasterizer
{
    //! This functions draw lines.
    bool clipLine(math::vec3 &p1, math::vec3 &p2, FrameBuffer *fb);
    void drawLine(const math::vertex &p1, const math::vertex &p2, FrameBuffer *fb);

public:
    WireframeTriangleRasterizer() { }

    void drawTriangle(const math::Triangle &t, FrameBuffer *fb);
};

}

#endif // WIREFRAMETRIANGLERASTERIZER_H
