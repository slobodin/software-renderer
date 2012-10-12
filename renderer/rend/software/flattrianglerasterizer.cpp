/*
 * flattrianglerasterizer.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "flattrianglerasterizer.h"

#include "poly.h"
#include "framebuffer.h"
#include "vertex.h"
#include "vec3.h"
#include "color.h"

namespace rend
{

inline void makeCCWTriangle(math::vertex &p1, math::vertex &p2, math::vertex &p3)
{
    // sort vertices (CCW order: p1 (top), p2, p3 (bottom))
    if (p2.p.y < p1.p.y)
        std::swap(p1, p2);

    if (p3.p.y < p1.p.y)
        std::swap(p1, p3);

    if (p3.p.y < p2.p.y)
        std::swap(p2, p3);
}

void FlatTriangleRasterizer::drawBottomTriangle(int x1, int y1,
                                                int x2, int /*y2*/,
                                                int x3, int y3,
                                                const Color3 &color,
                                                FrameBuffer *fb)
{
    // make ccw order
    if (x3 < x2)
        std::swap(x2, x3);

    double height = y3 - y1;
    double dxLeft = (x2 - x1) / height;
    double dxRight = (x3 - x1) / height;
    double xs = x1;
    double xe = x1;

    rasterizeTopOrBottomTriangle(x1, y1, x2, x3, y3, dxLeft, dxRight, xs, xe, color, fb);
}

void FlatTriangleRasterizer::drawTopTriangle(int x1, int y1,
                                             int x2, int /*y2*/,
                                             int x3, int y3,
                                             const Color3 &color,
                                             FrameBuffer *fb)
{
    // here is cw order
    if (x2 < x1)
        std::swap(x1, x2);

    double height = y3 - y1;
    double dx_left  = (x3 - x1) / height;
    double dx_right = (x3 - x2) / height;
    double xs = x1;
    double xe = x2;

    rasterizeTopOrBottomTriangle(x1, y1, x2, x3, y3, dx_left, dx_right, xs, xe, color, fb);
}

void FlatTriangleRasterizer::rasterizeTopOrBottomTriangle(int x1, int y1, int x2, int x3, int y3,
                                                          double dxLeft, double dxRight, double xs, double xe,
                                                          const Color3 &color, FrameBuffer *fb)
{
    int yorig = fb->yorig();
    int xorig = fb->xorig();
    int height = fb->height();
    int width = fb->width();

    // top of screen clipping
    if (y1 < yorig)
    {
        xs = xs + dxLeft * (-y1 + yorig);
        xe = xe + dxRight * (-y1 + yorig);

        y1 = yorig;
    }

    // bottom screen clipping
    if (y3 > height)
    {
        y3 = height - 1;
    }
    else
        y3 = y3 - 1;

    // if no x clipping (left right screen borders)
    if (x1 >= xorig && x1 <= width &&
        x2 >= xorig && x2 <= width &&
        x3 >= xorig && x3 <= width)
    {
        for (int y = y1; y <= y3; y++)
        {
            fb->wscanline(xs, xe, y, color);

            xs += dxLeft;
            xe += dxRight;
        }
    }
    else    // have x clipping
    {
        double left, right;
        for (int y = y1; y <= y3; y++)
        {
            left = xs; right = xe;

            xs += dxLeft;
            xe += dxRight;

            if (left < xorig)
            {
                left = xorig;

                if (right < xorig)
                    continue;
            }

            if (right > width)
            {
                right = width;

                if (left > width)
                    continue;
            }

            fb->wscanline(left, right, y, color);
        }
    }
}

void FlatTriangleRasterizer::drawTriangle(const math::Triangle &t, FrameBuffer *fb)
{
    math::vertex p1 = t.v(0);
    math::vertex p2 = t.v(1);
    math::vertex p3 = t.v(2);

    // check degenerate triangle
    if ((math::DCMP(p1.p.x, p2.p.x) && math::DCMP(p2.p.x, p3.p.x)) ||
        (math::DCMP(p1.p.y, p2.p.y) && math::DCMP(p2.p.y, p3.p.y)))
        return;

    makeCCWTriangle(p1, p2, p3);

    int x1 = p1.p.x, x2 = p2.p.x, x3 = p3.p.x;
    int y1 = p1.p.y, y2 = p2.p.y, y3 = p3.p.y;
    const Color3 &color = p1.color;

    // if triangle isn't on a screen
    if (y3 < fb->yorig() || y1 > fb->height() ||
       (x1 < fb->xorig() && x2 < fb->xorig() && x3 < fb->xorig()) ||
       (x1 > fb->width() && x2 > fb->width() && x3 > fb->width()))
        return;

    if (y1 == y2)
        drawTopTriangle(x1, y1, x2, y2, x3, y3, color, fb);
    else if (y2 == y3)
        drawBottomTriangle(x1, y1, x2, y2, x3, y3, color, fb);
    else
    {
        double newX = x1 + (y2 - y1) * (x3 - x1) / (y3 - y1);   // ctg * dy

        drawBottomTriangle(x1, y1, newX, y2, x2, y2, color, fb);
        drawTopTriangle(x2, y2, newX, y2, x3, y3, color, fb);
    }
}

}
