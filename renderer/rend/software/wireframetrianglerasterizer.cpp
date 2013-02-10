/*
 * wireframetrianglerasterizer.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "stdafx.h"

#include "wireframetrianglerasterizer.h"

#include "poly.h"
#include "framebuffer.h"
#include "vertex.h"
#include "vec3.h"
#include "color.h"

namespace rend
{

bool WireframeTriangleRasterizer::clipLine(math::vec3 &p1, math::vec3 &p2, FrameBuffer *fb)
{
    // internal clipping codes
    const int CLIP_CODE_C = 0x0000;
    const int CLIP_CODE_N = 0x0008;
    const int CLIP_CODE_S = 0x0004;
    const int CLIP_CODE_E = 0x0002;
    const int CLIP_CODE_W = 0x0001;

    const int CLIP_CODE_NE = 0x000a;
    const int CLIP_CODE_SE = 0x0006;
    const int CLIP_CODE_NW = 0x0009;
    const int CLIP_CODE_SW = 0x0005;

    int xc1 = static_cast<int>(p1.x),
        yc1 = static_cast<int>(p1.y),
        xc2 = static_cast<int>(p2.x),
        yc2 = static_cast<int>(p2.y);

    int p1_code = 0, p2_code = 0;

    // determine codes for p1 and p2
    if (p1.y < fb->yorig())
        p1_code |= CLIP_CODE_N;
    else
        if (p1.y > fb->height())
            p1_code |= CLIP_CODE_S;

    if (p1.x < fb->xorig())
        p1_code |= CLIP_CODE_W;
    else
        if (p1.x > fb->width())
            p1_code |= CLIP_CODE_E;

    if (p2.y < fb->yorig())
        p2_code |= CLIP_CODE_N;
    else
        if (p2.y > fb->height())
            p2_code |= CLIP_CODE_S;

    if (p2.x < fb->xorig())
        p2_code |= CLIP_CODE_W;
    else
        if (p2.x > fb->width())
            p2_code |= CLIP_CODE_E;

    // try and trivially reject
    if ((p1_code & p2_code))
        return false;

    // test for totally visible, if so leave points untouched
    if (p1_code == 0 && p2_code == 0)
        return true;

    // determine end clip point for p1
    switch(p1_code)
    {
    case CLIP_CODE_C:
        break;

    case CLIP_CODE_N:
        yc1 = fb->yorig();
        xc1 = p1.x + 0.5 + (fb->yorig() - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
        break;

    case CLIP_CODE_S:
        yc1 = fb->height();
        xc1 = p1.x + 0.5 + (fb->height() - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
        break;

    case CLIP_CODE_W:
        xc1 = fb->xorig();
        yc1 = p1.y + 0.5 + (fb->xorig() - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
        break;

    case CLIP_CODE_E:
        xc1 = fb->width();
        yc1 = p1.y + 0.5 + (fb->width() - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
        break;

    // these cases are more complex, must compute 2 intersections
    case CLIP_CODE_NE:
        // north hline intersection
        yc1 = fb->yorig();
        xc1 = p1.x + 0.5 + (fb->yorig() - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);

        // test if intersection is valid, of so then done, else compute next
        if (xc1 < fb->xorig() || xc1 > fb->width())
        {
            // east vline intersection
            xc1 = fb->width();
            yc1 = p1.y + 0.5 + (fb->width() - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
        }
        break;

    case CLIP_CODE_SE:
        // south hline intersection
        yc1 = fb->height();
        xc1 = p1.x + 0.5 + (fb->height() - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);

        // test if intersection is valid, of so then done, else compute next
        if (xc1 < fb->xorig() || xc1 > fb->width())
        {
            // east vline intersection
            xc1 = fb->width();
            yc1 = p1.y + 0.5 + (fb->width() - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
        }
        break;

    case CLIP_CODE_NW:
        // north hline intersection
        yc1 = fb->yorig();
        xc1 = p1.x + 0.5 + (fb->yorig() - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);

        // test if intersection is valid, of so then done, else compute next
        if (xc1 < fb->xorig() || xc1 > fb->width())
        {
            xc1 = fb->xorig();
            yc1 = p1.y + 0.5 + (fb->xorig() - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
        }
        break;

    case CLIP_CODE_SW:
        // south hline intersection
        yc1 = fb->height();
        xc1 = p1.x + 0.5 + (fb->height() - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);

        // test if intersection is valid, of so then done, else compute next
        if (xc1 < fb->xorig() || xc1 > fb->width())
        {
            xc1 = fb->xorig();
            yc1 = p1.y + 0.5 + (fb->xorig() - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
        }
        break;

    default:
        break;
    }

    // determine clip point for p2
    switch(p2_code)
    {
    case CLIP_CODE_C:
        break;

    case CLIP_CODE_N:
        yc2 = fb->yorig();
        xc2 = p2.x + (fb->yorig() - p2.y) * (p1.x - p2.x) / (p1.y - p2.y);
        break;

    case CLIP_CODE_S:
        yc2 = fb->height();
        xc2 = p2.x + (fb->height() - p2.y) * (p1.x - p2.x) / (p1.y - p2.y);
        break;

    case CLIP_CODE_W:
        xc2 = fb->xorig();
        yc2 = p2.y + (fb->xorig() - p2.x) * (p1.y - p2.y) / (p1.x - p2.x);
        break;

    case CLIP_CODE_E:
        xc2 = fb->width();
        yc2 = p2.y + (fb->width() - p2.x) * (p1.y - p2.y) / (p1.x - p2.x);
        break;

    // these cases are more complex, must compute 2 intersections
    case CLIP_CODE_NE:
        // north hline intersection
        yc2 = fb->yorig();
        xc2 = p2.x + 0.5 + (fb->yorig() - p2.y) * (p1.x - p2.x) / (p1.y - p2.y);

        // test if intersection is valid, of so then done, else compute next
        if (xc2 < fb->xorig() || xc2 > fb->width())
        {
            // east vline intersection
            xc2 = fb->width();
            yc2 = p2.y + 0.5 + (fb->width() - p2.x) * (p1.y - p2.y) / (p1.x - p2.x);
        }
        break;

    case CLIP_CODE_SE:
        // south hline intersection
        yc2 = fb->height();
        xc2 = p2.x + 0.5 + (fb->height() - p2.y) * (p1.x - p2.x) / (p1.y - p2.y);

        // test if intersection is valid, of so then done, else compute next
        if (xc2 < fb->xorig() || xc2 > fb->width())
        {
            // east vline intersection
            xc2 = fb->width();
            yc2 = p2.y + 0.5 + (fb->width() - p2.x) * (p1.y - p2.y) / (p1.x - p2.x);
        }
        break;

    case CLIP_CODE_NW:
        // north hline intersection
        yc2 = fb->yorig();
        xc2 = p2.x + 0.5 + (fb->yorig() - p2.y) * (p1.x - p2.x) / (p1.y - p2.y);

        // test if intersection is valid, of so then done, else compute next
        if (xc2 < fb->xorig() || xc2 > fb->width())
        {
            xc2 = fb->xorig();
            yc2 = p2.y + 0.5 + (fb->xorig() - p2.x) * (p1.y - p2.y) / (p1.x - p2.x);
        }
        break;

    case CLIP_CODE_SW:
        // south hline intersection
        yc2 = fb->height();
        xc2 = p2.x + 0.5 + (fb->height() - p2.y) * (p1.x - p2.x) / (p1.y - p2.y);

        // test if intersection is valid, of so then done, else compute next
        if (xc2 < fb->xorig() || xc2 > fb->width())
        {
            xc2 = fb->xorig();
            yc2 = p2.y + 0.5 + (fb->xorig() - p2.x) * (p1.y - p2.y) / (p1.x - p2.x);
        }
        break;

    default:
        break;
    }

    // do bounds check
    if ((xc1 < fb->xorig()) || (xc1 > fb->width()) ||
        (yc1 < fb->yorig()) || (yc1 > fb->height())||
        (xc2 < fb->xorig()) || (xc2 > fb->width()) ||
        (yc2 < fb->yorig()) || (yc2 > fb->height()))
    {
        return false;
    }

    // store vars back
    p1.x = xc1;
    p1.y = yc1;
    p2.x = xc2;
    p2.y = yc2;

    return true;
}

void WireframeTriangleRasterizer::drawLine(const math::vertex &p1, const math::vertex &p2, FrameBuffer *fb)
{
    math::vec3 pc1(p1.p), pc2(p2.p);

    int cols = fb->width();

    if (clipLine(pc1, pc2, fb))
    {
        int error;
        int x0 = pc1.x, x1 = pc2.x;
        int y0 = pc1.y, y1 = pc2.y;
        int pixNum;

        pixNum = y0 * cols + x0;

        int dx = x1 - x0;
        int dy = y1 - y0;

        int xInc, yInc;
        if (dx >= 0)
            xInc = 1;
        else
        {
            xInc = -1;
            dx = -dx;
        }

        if (dy >= 0)
            yInc = cols;
        else
        {
            yInc = -cols;
            dy = -dy;
        }

        int dx2 = dx * 2;
        int dy2 = dy * 2;

        if (dx > dy)
        {
            error = dy2 - dx;

            for (int index = 0; index <= dx; index++)
            {
                fb->wpixel(pixNum, p1.color);

                if (error >= 0)
                {
                    error -= dx2;
                    pixNum += yInc;
                }

                error += dy2;
                pixNum += xInc;
            }
        }
        else
        {
            error = dx2 - dy;

            for (int index = 0; index <= dy; index++)
            {
                fb->wpixel(pixNum, p1.color);

                if (error >= 0)
                {
                    error -= dy2;
                    pixNum += xInc;
                }

                error += dx2;
                pixNum += yInc;
            }
        }
    }
}

void WireframeTriangleRasterizer::drawTriangle(const math::Triangle &t, FrameBuffer *fb)
{
    drawLine(t.v(0), t.v(1), fb);
    drawLine(t.v(1), t.v(2), fb);
    drawLine(t.v(2), t.v(0), fb);
}

}
