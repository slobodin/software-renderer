/*
 * rasterizer.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "rasterizer.h"

#include "vec2.h"
#include "poly.h"
#include "viewport.h"
#include "texture.h"

namespace rend
{

// helpers
enum TriangleType
{
    TT_FLAT_TOP,
    TT_FLAT_BOTTOM,
    TT_FLAT_GENERAL
};

void Rasterizer::makeCCWTriangle(math::vertex &p1, math::vertex &p2, math::vertex &p3)
{
    // sort vertices (CCW order: p1 (top), p2, p3 (bottom))
    if (p2.p.y < p1.p.y)
        std::swap(p1, p2);

    if (p3.p.y < p1.p.y)
        std::swap(p1, p3);

    if (p3.p.y < p2.p.y)
        std::swap(p2, p3);
}

void Rasterizer::drawBottomTriangle(int x1, int y1,
                                    int x2, int /*y2*/,
                                    int x3, int y3,
                                    const Color3 &color)
{
    // make ccw order
    if (x3 < x2)
        std::swap(x2, x3);

    double height = y3 - y1;
    double dxLeft = (x2 - x1) / height;
    double dxRight = (x3 - x1) / height;
    double xs = x1;
    double xe = x1;

    rasterizeTopOrBottomTriangle(x1, y1, x2, x3, y3, dxLeft, dxRight, xs, xe, color);
}

void Rasterizer::drawTopTriangle(int x1, int y1,
                                 int x2, int /*y2*/,
                                 int x3, int y3,
                                 const Color3 &color)
{
    // here is cw order
    if (x2 < x1)
        std::swap(x1, x2);

    double height = y3 - y1;
    double dx_left  = (x3 - x1) / height;
    double dx_right = (x3 - x2) / height;
    double xs = x1;
    double xe = x2;

    rasterizeTopOrBottomTriangle(x1, y1, x2, x3, y3, dx_left, dx_right, xs, xe, color);
}

void Rasterizer::rasterizeTopOrBottomTriangle(int x1, int y1, int x2, int x3, int y3,
                                              double dxLeft, double dxRight, double xs, double xe,
                                              const Color3 &color)
{
    int iy1 = 0, iy3 = 0;

    // top of screen clipping
    if (y1 < m_fb.yorig())
    {
        xs = xs + dxLeft * (-y1 + m_fb.yorig());
        xe = xe + dxRight * (-y1 + m_fb.yorig());

        y1 = m_fb.yorig();
        iy1 = y1;     // ceiling
    }
    else
        iy1 = y1;

    // bottom screen clipping
    if (y3 > m_fb.height())
    {
        y3 = m_fb.height();
        iy3 = y3 - 1;
    }
    else
        iy3 = y3 - 1;

    // if no x clipping (left right screen borders)
    if (x1 >= m_fb.xorig() && x1 <= m_fb.width() &&
        x2 >= m_fb.xorig() && x2 <= m_fb.width() &&
        x3 >= m_fb.xorig() && x3 <= m_fb.width())
    {
        for (int y = iy1; y <= iy3; y++)
        {
            m_fb.wscanline(xs, xe, y, color);

            xs += dxLeft;
            xe += dxRight;
        }
    }
    else    // have x clipping
    {
        for (int y = iy1; y <= iy3; y++)
        {
            double left = xs, right = xe;

            xs += dxLeft;
            xe += dxRight;

            if (left < m_fb.xorig())
            {
                left = m_fb.xorig();

                if (right < m_fb.xorig())
                    continue;
            }

            if (right > m_fb.width())
            {
                right = m_fb.width();

                if (left > m_fb.width())
                    continue;
            }

            m_fb.wscanline(left, right, y, color);
        }
    }
}

void Rasterizer::drawBottomTriangleGouraud(math::vertex &v1, math::vertex &v2, math::vertex &v3)
{
    if (v3.p.x < v2.p.x)
        std::swap(v2, v3);

    /*int x1 = v1.p.x, x2 = v2.p.x, x3 = v3.p.x;
    int y1 = v1.p.y, y3 = v3.p.y;       // y2 equals to y2 (bottom flat triangle)

    double height = y3 - y1;
    double dxLeft = (x2 - x1) / height;
    double dxRight = (x3 - x1) / height;
    double xs = x1;
    double xe = x1;

    double rs = v1.color[RED];
    double re = v1.color[RED];
    double gs = v1.color[GREEN];
    double ge = v1.color[GREEN];
    double bs = v1.color[BLUE];
    double be = v1.color[BLUE];

    // horisontal interpolating
    int r = ir1, g = ig1, b = ib1;
    double dx = xe - xs;
    double dirx = (double)(re - rs) / dx;
    double digx = (double)(ge - gs) / dx;
    double dibx = (double)(be - bs) / dx;*/
}

void Rasterizer::drawTopTriangleGouraud(math::vertex &v1, math::vertex &v2, math::vertex &v3)
{
    if (v2.p.x < v1.p.x)
        std::swap(v1, v2);

//    int x1 = v1.p.x, x2 = v2.p.x, x3 = v3.p.x;
//    int y1 = v1.p.y, y3 = v3.p.y;
}

bool Rasterizer::clipLine(math::vec3 &p1, math::vec3 &p2)
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
    if (p1.y < m_fb.yorig())
        p1_code |= CLIP_CODE_N;
    else
        if (p1.y > m_fb.height())
            p1_code |= CLIP_CODE_S;

    if (p1.x < m_fb.xorig())
        p1_code |= CLIP_CODE_W;
    else
        if (p1.x > m_fb.width())
            p1_code |= CLIP_CODE_E;

    if (p2.y < m_fb.yorig())
        p2_code |= CLIP_CODE_N;
    else
        if (p2.y > m_fb.height())
            p2_code |= CLIP_CODE_S;

    if (p2.x < m_fb.xorig())
        p2_code |= CLIP_CODE_W;
    else
        if (p2.x > m_fb.width())
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
    case CLIP_CODE_C: break;

    case CLIP_CODE_N:
        yc1 = m_fb.yorig();
        xc1 = p1.x + 0.5 + (m_fb.yorig() - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);

        break;
    case CLIP_CODE_S:
        yc1 = m_fb.height();
        xc1 = p1.x + 0.5 + (m_fb.height() - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);

        break;
    case CLIP_CODE_W:
        xc1 = m_fb.xorig();
        yc1 = p1.y + 0.5 + (m_fb.xorig() - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);

        break;
    case CLIP_CODE_E:
        xc1 = m_fb.width();
        yc1 = p1.y + 0.5 + (m_fb.width() - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);

        break;
    // these cases are more complex, must compute 2 intersections
    case CLIP_CODE_NE:
        // north hline intersection
        yc1 = m_fb.yorig();
        xc1 = p1.x + 0.5 + (m_fb.yorig() - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);

        // test if intersection is valid, of so then done, else compute next
        if (xc1 < m_fb.xorig() || xc1 > m_fb.width())
        {
            // east vline intersection
            xc1 = m_fb.width();
            yc1 = p1.y + 0.5 + (m_fb.width() - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
        }

        break;
    case CLIP_CODE_SE:
        // south hline intersection
        yc1 = m_fb.height();
        xc1 = p1.x + 0.5 + (m_fb.height() - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);

        // test if intersection is valid, of so then done, else compute next
        if (xc1 < m_fb.xorig() || xc1 > m_fb.width())
        {
            // east vline intersection
            xc1 = m_fb.width();
            yc1 = p1.y + 0.5 + (m_fb.width() - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
        } // end if

        break;
    case CLIP_CODE_NW:
        // north hline intersection
        yc1 = m_fb.yorig();
        xc1 = p1.x + 0.5 + (m_fb.yorig() - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);

        // test if intersection is valid, of so then done, else compute next
        if (xc1 < m_fb.xorig() || xc1 > m_fb.width())
        {
            xc1 = m_fb.xorig();
            yc1 = p1.y + 0.5 + (m_fb.xorig() - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
        } // end if

        break;
    case CLIP_CODE_SW:
        // south hline intersection
        yc1 = m_fb.height();
        xc1 = p1.x + 0.5 + (m_fb.height() - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);

        // test if intersection is valid, of so then done, else compute next
        if (xc1 < m_fb.xorig() || xc1 > m_fb.width())
        {
            xc1 = m_fb.xorig();
            yc1 = p1.y + 0.5 + (m_fb.xorig() - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
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
        yc2 = m_fb.yorig();
        xc2 = p2.x + (m_fb.yorig() - p2.y) * (p1.x - p2.x) / (p1.y - p2.y);

        break;
    case CLIP_CODE_S:
        yc2 = m_fb.height();
        xc2 = p2.x + (m_fb.height() - p2.y) * (p1.x - p2.x) / (p1.y - p2.y);

        break;
    case CLIP_CODE_W:
        xc2 = m_fb.xorig();
        yc2 = p2.y + (m_fb.xorig() - p2.x) * (p1.y - p2.y) / (p1.x - p2.x);

        break;
    case CLIP_CODE_E:
        xc2 = m_fb.width();
        yc2 = p2.y + (m_fb.width() - p2.x) * (p1.y - p2.y) / (p1.x - p2.x);

        break;
        // these cases are more complex, must compute 2 intersections
    case CLIP_CODE_NE:
        // north hline intersection
        yc2 = m_fb.yorig();
        xc2 = p2.x + 0.5 + (m_fb.yorig() - p2.y) * (p1.x - p2.x) / (p1.y - p2.y);

        // test if intersection is valid, of so then done, else compute next
        if (xc2 < m_fb.xorig() || xc2 > m_fb.width())
        {
            // east vline intersection
            xc2 = m_fb.width();
            yc2 = p2.y + 0.5 + (m_fb.width() - p2.x) * (p1.y - p2.y) / (p1.x - p2.x);
        }

        break;
    case CLIP_CODE_SE:
        // south hline intersection
        yc2 = m_fb.height();
        xc2 = p2.x + 0.5 + (m_fb.height() - p2.y) * (p1.x - p2.x) / (p1.y - p2.y);

        // test if intersection is valid, of so then done, else compute next
        if (xc2 < m_fb.xorig() || xc2 > m_fb.width())
        {
            // east vline intersection
            xc2 = m_fb.width();
            yc2 = p2.y + 0.5 + (m_fb.width() - p2.x) * (p1.y - p2.y) / (p1.x - p2.x);
        }

        break;
    case CLIP_CODE_NW:
        // north hline intersection
        yc2 = m_fb.yorig();
        xc2 = p2.x + 0.5 + (m_fb.yorig() - p2.y) * (p1.x - p2.x) / (p1.y - p2.y);

        // test if intersection is valid, of so then done, else compute next
        if (xc2 < m_fb.xorig() || xc2 > m_fb.width())
        {
            xc2 = m_fb.xorig();
            yc2 = p2.y + 0.5 + (m_fb.xorig() - p2.x) * (p1.y - p2.y) / (p1.x - p2.x);
        }

        break;
    case CLIP_CODE_SW:
        // south hline intersection
        yc2 = m_fb.height();
        xc2 = p2.x + 0.5 + (m_fb.height() - p2.y) * (p1.x - p2.x) / (p1.y - p2.y);

        // test if intersection is valid, of so then done, else compute next
        if (xc2 < m_fb.xorig() || xc2 > m_fb.width())
        {
            xc2 = m_fb.xorig();
            yc2 = p2.y + 0.5 + (m_fb.xorig() - p2.x) * (p1.y - p2.y) / (p1.x - p2.x);
        }

        break;
    default:
        break;
    }

    // do bounds check
    if ((xc1 < m_fb.xorig()) || (xc1 > m_fb.width()) ||
        (yc1 < m_fb.yorig()) || (yc1 > m_fb.height())||
        (xc2 < m_fb.xorig()) || (xc2 > m_fb.width()) ||
        (yc2 < m_fb.yorig()) || (yc2 > m_fb.height()))
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

void Rasterizer::drawLine(const math::vertex &p1, const math::vertex &p2)
{
    math::vec3 pc1(p1.p), pc2(p2.p);
    const Color3 &color = p1.color;

    int cols = m_fb.width();

    if (clipLine(pc1, pc2))
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

        int dx2 = dx << 1;
        int dy2 = dy << 1;

        if (dx > dy)
        {
            error = dy2 - dx;

            for (int index = 0; index <= dx; index++)
            {
                m_fb.wpixel(pixNum, color);

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
                m_fb.wpixel(pixNum, color);

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

void Rasterizer::drawFillTriangle(math::vertex &p1,
                                  math::vertex &p2,
                                  math::vertex &p3)
{
    // check degenerate triangle
    if ((p1.p.x == p2.p.x && p2.p.x == p3.p.x) ||
        (p1.p.y == p2.p.y && p2.p.y == p3.p.y))
        return;

    makeCCWTriangle(p1, p2, p3);

    int x1 = p1.p.x, x2 = p2.p.x, x3 = p3.p.x;
    int y1 = p1.p.y, y2 = p2.p.y, y3 = p3.p.y;
    const Color3 &color = p1.color;

    // if triangle isn't on a screen
    if (y3 < m_fb.yorig() || y1 > m_fb.height() ||
       (x1 < m_fb.xorig() && x2 < m_fb.xorig() && x3 < m_fb.xorig()) ||
       (x1 > m_fb.width() && x2 > m_fb.width() && x3 > m_fb.width()))
        return;

    if (y1 == y2)
        drawTopTriangle(x1, y1, x2, y2, x3, y3, color);
    else if (y2 == y3)
        drawBottomTriangle(x1, y1, x2, y2, x3, y3, color);
    else
    {
        double newX = x1 + (y2 - y1) * (x3 - x1) / (y3 - y1);   // ctg * dy

        drawBottomTriangle(x1, y1, newX, y2, x2, y2, color);
        drawTopTriangle(x2, y2, newX, y2, x3, y3, color);
    }
}

void Rasterizer::drawFillTriangle(const math::Triangle &tr)
{
    math::vertex v1 = tr.v(0);
    math::vertex v2 = tr.v(1);
    math::vertex v3 = tr.v(2);

    drawFillTriangle(v1, v2, v3);
}

void Rasterizer::drawTriangle(const math::vertex &p1, const math::vertex &p2, const math::vertex &p3)
{
    drawLine(p1, p2);
    drawLine(p2, p3);
    drawLine(p3, p1);
}

void Rasterizer::drawTriangle(const math::Triangle &tr)
{
    drawTriangle(tr.v(0), tr.v(1), tr.v(2));
}

void Rasterizer::drawGouraudTriangle(math::vertex &v1, math::vertex &v2, math::vertex &v3)
{
    // check degenerate triangle
    if ((v1.p.x == v2.p.x && v2.p.x == v3.p.x) ||
        (v1.p.y == v2.p.y && v2.p.y == v3.p.y))
        return;

    makeCCWTriangle(v1, v2, v3);

    int x1 = v1.p.x, x2 = v2.p.x, x3 = v3.p.x;
    int y1 = v1.p.y, y2 = v2.p.y, y3 = v3.p.y;

    // if triangle isn't on a screen
    if (y3 < m_fb.yorig() || y1 > m_fb.height() ||
       (x1 < m_fb.xorig() && x2 < m_fb.xorig() && x3 < m_fb.xorig()) ||
       (x1 > m_fb.width() && x2 > m_fb.width() && x3 > m_fb.width()))
        return;

    if (y1 == y2)
        drawTopTriangleGouraud(v1, v2, v3);
    else if (y2 == y3)
        drawBottomTriangleGouraud(v1, v2, v3);
    else
    {
        math::vertex newV = v2;

        double dy = ((double)y2 - y1) / ((double)y3 - y1);
        double newX = x1 + dy * (x3 - x1);

        newV.p.x = newX;
        newV.color = Color3::lerp(v1.color, v3.color, dy);

        drawBottomTriangleGouraud(v1, newV, v2);
        drawTopTriangleGouraud(v2, newV, v3);
    }
}

void Rasterizer::drawGouraudTriangle(const math::Triangle &tr)
{
    math::vertex v1 = tr.v(0);
    math::vertex v2 = tr.v(1);
    math::vertex v3 = tr.v(2);

    drawGouraudTriangle(v1, v2, v3);
}

void Rasterizer::drawTexturedTriangle(const math::Triangle &tr)
{
    math::vertex v0 = tr.v(0);
    math::vertex v1 = tr.v(1);
    math::vertex v2 = tr.v(2);

    v0.t.x *= (double)tr.getMaterial()->texture->width() - 1.;
    v0.t.y *= (double)tr.getMaterial()->texture->height() - 1.;
    v1.t.x *= (double)tr.getMaterial()->texture->width() - 1.;
    v1.t.y *= (double)tr.getMaterial()->texture->height() - 1.;
    v2.t.x *= (double)tr.getMaterial()->texture->width() - 1.;
    v2.t.y *= (double)tr.getMaterial()->texture->height() - 1.;

    // first trivial clipping rejection tests
    if (((v0.p.y < m_fb.yorig())  &&
         (v1.p.y < m_fb.yorig())  &&
         (v2.p.y < m_fb.yorig())) ||

        ((v0.p.y > m_fb.height())  &&
         (v1.p.y > m_fb.height())  &&
         (v2.p.y > m_fb.height())) ||

        ((v0.p.x < m_fb.xorig())  &&
         (v1.p.x < m_fb.xorig())  &&
         (v2.p.x < m_fb.xorig())) ||

        ((v0.p.x > m_fb.width())  &&
         (v1.p.x > m_fb.width())  &&
         (v2.p.x > m_fb.width())))
       return;

    // degenerate triangle
    if ( ((v0.p.x==v1.p.x) && (v1.p.x==v2.p.x)) ||
         ((v0.p.y==v1.p.y) && (v1.p.y==v2.p.y)))
       return;

    // sort vertices
    if (v1.p.y < v0.p.y)
        std::swap(v1, v0);
    if (v2.p.y < v0.p.y)
        std::swap(v2, v0);
    if (v2.p.y < v1.p.y)
        std::swap(v2, v1);

    TriangleType tri_type;

    // now test for trivial flat sided cases
    if (v0.p.y==v1.p.y)
    {
        tri_type = TT_FLAT_TOP;
        if (v1.p.x < v0.p.x)
            std::swap(v1, v0);
    }
    else
    // now test for trivial flat sided cases
    if (v1.p.y==v2.p.y)
        {
        // set triangle type
        tri_type = TT_FLAT_BOTTOM;

        // sort vertices left to right
        if (v2.p.x < v1.p.x)
            std::swap(v2, v1);

        } // end if
    else
        {
        // must be a general triangle
        tri_type = TT_FLAT_GENERAL;

        } // end else

    // extract base color of lit poly, so we can modulate texture a bit
    // for lighting
    int r_base = v0.color[RED];
    int g_base = v0.color[GREEN];
    int b_base = v0.color[BLUE];

    // extract vertices for processing, now that we have order
    double x0  = (double)(v0.p.x+0.5);
    double y0  = (double)(v0.p.y+0.5);
    double tu0 = (double)(v0.t.x);
    double tv0 = (double)(v0.t.y);

    double x1  = (double)(v1.p.x+0.5);
    double y1  = (double)(v1.p.y+0.5);
    double tu1 = (double)(v1.t.x);
    double tv1 = (double)(v1.t.y);

    double x2  = (double)(v2.p.x+0.5);
    double y2  = (double)(v2.p.y+0.5);
    double tu2 = (double)(v2.t.x);
    double tv2 = (double)(v2.t.y);

    // set interpolation restart value
    double yrestart = y1;

    // what kind of triangle
    double dy, dxdyl, dudyl, dvdyl;
    double dxdyr, dudyr, dvdyr;
    double xl, ul, vl, xr, ur, vr;
    double ystart, yend;

}

Rasterizer::Rasterizer(const int width, const int height)
    : m_fb(width, height)
{
}

void Rasterizer::rasterize(const RenderList &rendlist)
{
    auto &trias = rendlist.triangles();

    // painter's algorithm
    BOOST_REVERSE_FOREACH(const math::Triangle &t, trias)
    {
        if (!t.getMaterial())
        {
            syslog << "Material has not been setted for this triangle" << logdebug;
            continue;
        }

        switch(t.getMaterial()->shadeMode)
        {
        case Material::SM_WIRE:
            drawTriangle(t);
            break;

        case Material::SM_PLAIN_COLOR:
            drawFillTriangle(t);
            break;

        case Material::SM_FLAT:
            drawFillTriangle(t);
            break;

        case Material::SM_GOURAUD:
            drawGouraudTriangle(t);
            break;

        case Material::SM_TEXTURE:
            drawTexturedTriangle(t);
            break;

        default:
            syslog << "Unsupported shading mode." << logdebug;
            break;
        }
    }
}

void Rasterizer::beginFrame(sptr(Viewport) /*viewport*/)
{
    m_fb.clear();
}

void Rasterizer::endFrame(sptr(Viewport) viewport)
{
    viewport->flush(m_fb);
}

void Rasterizer::resize(int w, int h)
{
    m_fb.resize(w, h);
}

}
