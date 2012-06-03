/*
 * rasterizer.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "rasterizer.h"

#include "vec2.h"
#include "poly.h"

namespace rend
{

// helpers
enum TriangleType
{
    TT_FLAT_TOP,
    TT_FLAT_BOTTOM,
    TT_FLAT_GENERAL
};

void Rasterizer::drawBottomTriangle(int x1, int y1,
                                    int x2, int /*y2*/,
                                    int x3, int y3,
                                    const Color3 &color)
{
    if (x3 < x2)
        std::swap(x2, x3);

    double height = y3 - y1;
    double dxLeft = (x2 - x1) / height;
    double dxRight = (x3 - x1) / height;
    double xs = x1;
    double xe = x1;

    int iy1 = 0, iy3 = 0;

    if (y1 < m_fb.yorig())
    {
        xs = xs + dxLeft * (-y1 + m_fb.yorig());
        xe = xe + dxRight * (-y1 + m_fb.yorig());

        y1 = m_fb.yorig();
        iy1 = m_fb.yorig();
    }
    else
    {
        iy1 = y1;

        xs = xs + dxLeft * (iy1 - y1);
        xe = xe + dxRight * (iy1 - y1);
    }
    if (y3 > m_fb.height())
    {
        y3 = m_fb.height();
        iy3 = y3 - 1;
    }
    else
    {
        iy3 = y3 - 1;
    }

    if (x1 >= m_fb.xorig() && x1 <= m_fb.width() &&
        x2 >= m_fb.xorig() && x2 <= m_fb.width() &&
        x3 >= m_fb.xorig() && x3 <= m_fb.width())
    {
        for (int y = y1; y <= iy3; y++)
        {
            m_fb.wscanline(xs, xe, y, color);

            xs += dxLeft;
            xe += dxRight;
        }
    }
    else
    {
        for (int y = y1; y <= iy3; y++)
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

void Rasterizer::drawTopTriangle(int x1, int y1,
                                 int x2, int /*y2*/,
                                 int x3, int y3,
                                 const Color3 &color)
{
    if (x2 < x1)
    {
        std::swap(x1, x2);
    }

    double height = y3 - y1;

    double dx_left  = (x3 - x1) / height;
    double dx_right = (x3 - x2) / height;
    double xs = x1;
    double xe = x2;

    int iy1 = 0, iy3 = 0;

    if (y1 < m_fb.yorig())
    {
        xs = xs + dx_left * (-y1 + m_fb.yorig());
        xe = xe + dx_right * (-y1 + m_fb.yorig());

        y1 = m_fb.yorig();

        iy1 = y1;
    }
    else
    {
        iy1 = y1;

        xs = xs + dx_left * (iy1 - y1);
        xe = xe + dx_right * (iy1 - y1);
    }

    if (y3 > m_fb.height())
    {
        y3 = m_fb.height();

        iy3 = y3 - 1;
    }
    else
    {
        iy3 = y3 - 1;
    }

    if (x1 >= m_fb.xorig() && x1 <= m_fb.width() &&
        x2 >= m_fb.xorig() && x2 <= m_fb.width() &&
        x3 >= m_fb.xorig() && x3 <= m_fb.width())
    {
        for (int y = iy1; y <= iy3; y++)
        {

            m_fb.wscanline(xs, xe, y, color);

            xs += dx_left;
            xe += dx_right;
        }

    }
    else
    {
        for (int y = iy1; y <= iy3; y++)
        {
            double left = xs;
            double right = xe;

            xs += dx_left;
            xe += dx_right;

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
    Color3 color = p1.color;

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

void Rasterizer::drawFillTriangle(const math::vertex &p1,
                                  const math::vertex &p2,
                                  const math::vertex &p3)
{
    int x1 = p1.p.x, x2 = p2.p.x, x3 = p3.p.x;
    int y1 = p1.p.y, y2 = p2.p.y, y3 = p3.p.y;
    const Color3 &color = p1.color;

    if ((x1 == x2 && x2 == x3) || (y1 == y2 && y2 == y3))
        return;

    // sort vertices
    if (y2 < y1)
    {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    if (y3 < y1)
    {
        std::swap(x1, x3);
        std::swap(y1, y3);
    }

    if (y3 < y2)
    {
        std::swap(x2, x3);
        std::swap(y2, y3);
    }

    if (y3 < m_fb.yorig() || y1 > m_fb.height()
            || (x1 < m_fb.xorig() && x2 < m_fb.xorig() && x3 < m_fb.xorig())
            || (x1 > m_fb.width() && x2 > m_fb.width() && x3 > m_fb.width()))
        return;

    if (y1 == y2)
    {
        drawTopTriangle(x1, y1, x2, y2, x3, y3, color);
    }
    else if (y2 == y3)
    {
        drawBottomTriangle(x1, y1, x2, y2, x3, y3, color);
    }
    else
    {
        double newX = x1 + (y2 - y1) * (x3 - x1) / (y3 - y1);

        drawBottomTriangle(x1, y1, newX, y2, x2, y2, color);
        drawTopTriangle(x2, y2, newX, y2, x3, y3, color);
    }
}

void Rasterizer::drawFillTriangle(const math::Triangle &tr)
{
    drawFillTriangle(tr.v(0), tr.v(1), tr.v(2));
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

void Rasterizer::drawGouraudTriangle(const math::vertex &v1, const math::vertex &v2, const math::vertex &v3)
{
    math::vec3 p0(v1.p), p1(v2.p), p2(v3.p);

    if (((p0.y < m_fb.yorig()) && (p1.y < m_fb.yorig()) && (p2.y < m_fb.yorig()))
            || ((p0.y > m_fb.height()) && (p1.y > m_fb.height()) && (p2.y > m_fb.height()))
            || ((p0.x < m_fb.xorig()) && (p1.x < m_fb.xorig()) && (p2.x < m_fb.xorig()))
            || ((p0.x > m_fb.width()) && (p1.x > m_fb.width()) && (p2.x > m_fb.width())))
        return;

    // degenerate triangle
    if ((math::DCMP(p0.x, p1.x) && math::DCMP(p1.x, p2.x))
            || (math::DCMP(p0.y, p1.y) && math::DCMP(p1.y, p2.y)))
        return;

    // sort vertices
    if (p1.y < p0.y)
        std::swap(p0, p1);
    if (p2.y < p0.y)
        std::swap(p0, p2);
    if (p2.y < p1.y)
        std::swap(p1, p2);

    TriangleType triangleType;
    if (p0.y == p1.y)
    {
        triangleType = TT_FLAT_TOP;
        if (p1.x < p0.x)
            std::swap(p0, p1);
    }
    else if (p1.y == p2.y)
    {
        triangleType = TT_FLAT_BOTTOM;
        if (p2.x < p1.x)
            std::swap(p1, p2);
    }
    else
    {
        triangleType = TT_FLAT_GENERAL;
    }

    int x0 = (int)(p0.x + 0.5);
    int y0 = (int)(p0.y + 0.5);
    int x1 = (int)(p1.x + 0.5);
    int y1 = (int)(p1.y + 0.5);
    int x2 = (int)(p2.x + 0.5);
    int y2 = (int)(p2.y + 0.5);

    int yStart;
    int xl, xr, rl, gl, bl, rr, gr, br;
    // Maybe double???
    double dxdyl, drdyl, dgdyl, dbdyl;
    double dxdyr, drdyr, dgdyr, dbdyr;
    double dy, dyl, dyr;
    int yEnd;

    const int INTERP_LHS = 0;
    const int INTERP_RHS = 1;

    int irestart = INTERP_LHS;
    int yrestart = y1;

    // FIXME:
    int tr0 = v1.color[RED], tg0 = v1.color[GREEN], tb0 = v1.color[BLUE];
    int tr1 = v2.color[RED], tg1 = v2.color[GREEN], tb1 = v2.color[BLUE];
    int tr2 = v3.color[RED], tg2 = v3.color[GREEN], tb2 = v3.color[BLUE];

    if (triangleType != TT_FLAT_GENERAL)
    {
        if (triangleType == TT_FLAT_TOP)
        {
            dy = y2 - y0;

            dxdyl = (x2 - x0) / dy;
            drdyl = (tr2 - tr0) / dy;
            dgdyl = (tg2 - tg0) / dy;
            dbdyl = (tb2 - tb0) / dy;

            dxdyr = (x2 - x1) / dy;
            drdyr = (tr2 - tr1) / dy;
            dgdyr = (tg2 - tg1) / dy;
            dbdyr = (tb2 - tb1) / dy;

            // test for y clipping
            if (y0 < m_fb.yorig())
            {
                dy = (m_fb.yorig() - y0);

                xl = dxdyl * dy + x0;
                xr = dxdyr * dy + x1;

                rl = drdyl * dy + tr0;
                gl = dgdyl * dy + tg0;
                bl = dbdyl * dy + tb0;

                rr = drdyr * dy + tr1;
                gr = dgdyr * dy + tg1;
                br = dbdyr * dy + tb1;

                yStart = m_fb.yorig();
            }
            else
            {
                xl = x0;
                xr = x1;

                rl = tr0;
                gl = tg0;
                bl = tb0;

                rr = tr1;
                gr = tg1;
                br = tb1;

                yStart = y0;
            }
        }
        else    // flat bottom
        {
            dy = y1 - y0;

            dxdyl = (x1 - x0) / dy;
            drdyl = (tr1 - tr0) / dy;
            dgdyl = (tg1 - tg0) / dy;
            dbdyl = (tb1 - tb0) / dy;

            dxdyr = (x2 - x0) / dy;
            drdyr = (tr2 - tr0) / dy;
            dgdyr = (tg2 - tg0) / dy;
            dbdyr = (tb2 - tb0) / dy;

            // test for y clipping
            if (y0 < m_fb.yorig())
            {
                // compute overclip
                dy = m_fb.yorig() - y0;

                xl = dxdyl * dy + x0;
                xr = dxdyr * dy + x0;

                rl = drdyl * dy + tr0;
                gl = dgdyl * dy + tg0;
                bl = dbdyl * dy + tb0;

                rr = drdyr * dy + tr0;
                gr = dgdyr * dy + tg0;
                br = dbdyr * dy + tb0;

                // compute new starting y
                yStart = m_fb.yorig();
            }
            else // no clipping
            {
                // set starting values
                xl = x0;
                xr = x0;

                rl = tr0;
                gl = tg0;
                bl = tb0;

                rr = tr0;
                gr = tg0;
                br = tb0;

                // set starting y
                yStart = y0;
            }
        }

        // test for bottom clip, always
        if ((yEnd = y2) > m_fb.height())
            yEnd = m_fb.height();

        // test for horizontal clipping
        if ((x0 < m_fb.xorig()) || (x0 > m_fb.width())
                || (x1 < m_fb.xorig()) || (x1 > m_fb.width())
                || (x2 < m_fb.xorig()) || (x2 > m_fb.width()))
        {
            // clip version
            for (int yi = yStart; yi <= yEnd; yi++)
            {
                // compute span endpoints
                int xStart = xl;
                int xEnd = xr; // + FIXP16_ROUND_UP

                // compute starting points for u,v,w interpolants
                int ri = rl;
                int gi = gl;
                int bi = bl;

                int dx = xEnd - xStart;
                int dr, dg, db;

                // compute u, v interpolants
                if (dx > 0)
                {
                    dr = (rr - rl) / dx;
                    dg = (gr - gl) / dx;
                    db = (br - bl) / dx;
                }
                else
                {
                    dr = rr - rl;
                    dg = gr - gl;
                    db = br - bl;
                }

                // test for x clipping, LHS
                if (xStart < m_fb.xorig())
                {
                    // compute x overlap
                    dx = m_fb.xorig() - xStart;

                    // slide interpolants over
                    ri += dx * dr;
                    gi += dx * dg;
                    bi += dx * db;

                    // reset vars
                    xStart = m_fb.xorig();
                }

                // test for x clipping RHS
                if (xEnd > m_fb.width())
                    xEnd = m_fb.width();

                // draw span
                for (int xi = xStart; xi <= xEnd; xi++)
                {
                    m_fb.wpixel(xi, yi, Color3(ri, gi, bi));

                    // interpolate u, v
                    ri += dr;
                    gi += dg;
                    bi += db;
                }

                // interpolate r, g, b, x along right and left edge
                xl += dxdyl;
                rl += drdyl;
                gl += dgdyl;
                bl += dbdyl;

                xr += dxdyr;
                rr += drdyr;
                gr += dgdyr;
                br += dbdyr;
            }
        }
        else
        {
            // non-clip version
            for (int yi = yStart; yi <= yEnd; yi++)
            {
                // compute span endpoints
                int xStart = xl;
                int xEnd = xr;

                // compute starting points for u,v,w interpolants
                int ri = rl;
                int gi = gl;
                int bi = bl;

                // compute u, v interpolants
                int dx = xEnd - xStart;
                int dr, dg, db;

                if (dx > 0)
                {
                    dr = (rr - rl) / dx;
                    dg = (gr - gl) / dx;
                    db = (br - bl) / dx;
                }
                else
                {
                    dr = rr - rl;
                    dg = gr - gl;
                    db = br - bl;
                }

                // draw span
                for (int xi = xStart; xi <= xEnd; xi++)
                {
                    // write textel 5.6.5
                    m_fb.wpixel(xi, yi, Color3(ri, gi, bi));

                    // interpolate u,v
                    ri += dr;
                    gi += dg;
                    bi += db;
                }

                // interpolate r, g, b, x along right and left edge
                xl += dxdyl;
                rl += drdyl;
                gl += dgdyl;
                bl += dbdyl;

                xr += dxdyr;
                rr += drdyr;
                gr += dgdyr;
                br += dbdyr;
            }
        }
    }
    else
    {
        // first test for bottom clip, always
        if ((yEnd = y2) > m_fb.height())
            yEnd = m_fb.height();

        // pre-test y clipping status
        if (y1 < m_fb.yorig())
        {
            // compute all deltas
            // LHS
            dyl = y2 - y1;

            dxdyl = (x2  - x1) / dyl;
            drdyl = (tr2 - tr1) / dyl;
            dgdyl = (tg2 - tg1) / dyl;
            dbdyl = (tb2 - tb1) / dyl;

            // RHS
            dyr = y2 - y0;

            dxdyr = (x2  - x0) / dyr;
            drdyr = (tr2 - tr0) / dyr;
            dgdyr = (tg2 - tb0) / dyr;
            dbdyr = (tb2 - tb0) / dyr;

            // compute overclip
            dyr = m_fb.yorig() - y0;
            dyl = m_fb.yorig() - y1;

            // computer new LHS starting values
            xl = dxdyl * dyl + x1;

            rl = drdyl * dyl + tr1;
            gl = dgdyl * dyl + tg1;
            bl = dbdyl * dyl + tb1;

            // compute new RHS starting values
            xr = dxdyr * dyr + x0;

            rr = drdyr * dyr + tr0;
            gr = dgdyr * dyr + tg0;
            br = dbdyr * dyr + tb0;

            // compute new starting y
            yStart = m_fb.yorig();

            // test if we need swap to keep rendering left to right
            if (dxdyr > dxdyl)
            {
                std::swap(dxdyl, dxdyr);
                std::swap(drdyl, drdyr);
                std::swap(dgdyl, dgdyr);
                std::swap(dbdyl, dbdyr);
                std::swap(xl, xr);
                std::swap(rl, rr);
                std::swap(gl, gr);
                std::swap(bl, br);
                std::swap(x1, x2);
                std::swap(y1, y2);
                std::swap(tr1, tr2);
                std::swap(tg1, tg2);
                std::swap(tb1, tb2);

                // set interpolation restart
                irestart = INTERP_RHS;
            }
        }
        else if (y0 < m_fb.yorig())
        {
            // compute all deltas
            // LHS
            dyl = y1 - y0;

            dxdyl = (x1  - x0) / dyl;
            drdyl = (tr1 - tr0) / dyl;
            dgdyl = (tg1 - tg0) / dyl;
            dbdyl = (tb1 - tb0) / dyl;

            // RHS
            dyr = y2 - y0;

            dxdyr = (x2  - x0) / dyr;
            drdyr = (tr2 - tr0) / dyr;
            dgdyr = (tg2 - tg0) / dyr;
            dbdyr = (tb2 - tb0) / dyr;

            // compute overclip
            dy = (m_fb.yorig() - y0);

            // computer new LHS starting values
            xl = dxdyl * dy + x0;
            rl = drdyl * dy + tr0;
            gl = dgdyl * dy + tg0;
            bl = dbdyl * dy + tb0;

            // compute new RHS starting values
            xr = dxdyr * dy + x0;
            rr = drdyr * dy + tr0;
            gr = dgdyr * dy + tg0;
            br = dbdyr * dy + tb0;

            // compute new starting y
            yStart = m_fb.yorig();

            // test if we need swap to keep rendering left to right
            if (dxdyr < dxdyl)
            {
                std::swap(dxdyl, dxdyr);
                std::swap(drdyl, drdyr);
                std::swap(dgdyl, dgdyr);
                std::swap(dbdyl, dbdyr);
                std::swap(xl, xr);
                std::swap(rl, rr);
                std::swap(gl, gr);
                std::swap(bl, br);
                std::swap(x1, x2);
                std::swap(y1, y2);
                std::swap(tr1, tr2);
                std::swap(tg1, tg2);
                std::swap(tb1, tb2);

                // set interpolation restart
                irestart = INTERP_RHS;
            }
        }
        else
        {
            // no initial y clipping

            // compute all deltas
            // LHS
            dyl = y1 - y0;

            dxdyl = (x1  - x0) / dyl;
            drdyl = (tr1 - tr0) / dyl;
            dgdyl = (tg1 - tg0) / dyl;
            dbdyl = (tb1 - tb0) / dyl;

            // RHS
            dyr = (y2 - y0);

            dxdyr = (x2 - x0) / dyr;
            drdyr = (tr2 - tr0) / dyr;
            dgdyr = (tg2 - tg0) / dyr;
            dbdyr = (tb2 - tb0) / dyr;

            // no clipping y

            // set starting values
            xl = x0;
            xr = x0;

            rl = tr0;
            gl = tg0;
            bl = tb0;

            rr = tr0;
            gr = tg0;
            br = tb0;

            // set starting y
            yStart = y0;

            // test if we need swap to keep rendering left to right
            if (dxdyr < dxdyl)
            {
                std::swap(dxdyl, dxdyr);
                std::swap(drdyl, drdyr);
                std::swap(dgdyl, dgdyr);
                std::swap(dbdyl, dbdyr);
                std::swap(xl, xr);
                std::swap(rl, rr);
                std::swap(gl, gr);
                std::swap(bl, br);
                std::swap(x1, x2);
                std::swap(y1, y2);
                std::swap(tr1, tr2);
                std::swap(tg1, tg2);
                std::swap(tb1, tb2);

                // set interpolation restart
                irestart = INTERP_RHS;
            }
        }

        // test for horizontal clipping
        if ((x0 < m_fb.xorig()) || (x0 > m_fb.width()) ||
            (x1 < m_fb.xorig()) || (x1 > m_fb.width()) ||
            (x2 < m_fb.xorig()) || (x2 > m_fb.width()))
        {
            // clip version
            // x clipping

            for (int yi = yStart; yi <= yEnd; yi++)
            {
                // compute span endpoints
                int xStart = xl;
                int xEnd = xr;

                // compute starting points for r, g, b interpolants
                int ri = rl;
                int gi = gl;
                int bi = bl;

                int dx = xEnd - xStart;
                int dr, dg, db;
                // compute u, v interpolants
                if (dx > 0)
                {
                    dr = (rr - rl) / dx;
                    dg = (gr - gl) / dx;
                    db = (br - bl) / dx;
                }
                else
                {
                    dr = (rr - rl);
                    dg = (gr - gl);
                    db = (br - bl);
                }

                // test for x clipping, LHS
                if (xStart < m_fb.xorig())
                {
                    // compute x overlap
                    dx = m_fb.xorig() - xStart;

                    // slide interpolants over
                    ri += dx * dr;
                    gi += dx * dg;
                    bi += dx * db;

                    // set x to left clip edge
                    xStart = m_fb.xorig();
                }

                // test for x clipping RHS
                if (xEnd > m_fb.width())
                    xEnd = m_fb.width();

                // draw span
                for (int xi = xStart; xi <= xEnd; xi++)
                {
                    m_fb.wpixel(xi, yi, Color3(ri, gi, bi));

                    // interpolate r, g, b
                    ri += dr;
                    gi += dg;
                    bi += db;
                }

                // interpolate r, g, b, x along right and left edge
                xl += dxdyl;
                rl += drdyl;
                gl += dgdyl;
                bl += dbdyl;

                xr += dxdyr;
                rr += drdyr;
                gr += dgdyr;
                br += dbdyr;

                // test for yi hitting second region, if so change interpolant
                if (yi == yrestart)
                {
                    // test interpolation side change flag

                    if (irestart == INTERP_LHS)
                    {
                        // LHS
                        dyl = (y2 - y1);

                        dxdyl = (x2 - x1) / dyl;
                        drdyl = (tr2 - tr1) / dyl;
                        dgdyl = (tg2 - tg1) / dyl;
                        dbdyl = (tb2 - tb1) / dyl;

                        // set starting values
                        xl = x1;
                        rl = tr1;
                        gl = tg1;
                        bl = tb1;

                        // interpolate down on LHS to even up
                        xl += dxdyl;
                        rl += drdyl;
                        gl += dgdyl;
                        bl += dbdyl;
                    }
                    else
                    {
                        // RHS
                        dyr = (y1 - y2);

                        dxdyr = (x1 - x2) / dyr;
                        drdyr = (tr1 - tr2) / dyr;
                        dgdyr = (tg1 - tg2) / dyr;
                        dbdyr = (tb1 - tb2) / dyr;

                        // set starting values
                        xr = x2;
                        rr = tr2;
                        gr = tg2;
                        br = tb2;

                        // interpolate down on RHS to even up
                        xr += dxdyr;
                        rr += drdyr;
                        gr += dgdyr;
                        br += dbdyr;
                    }
                }
            }
        }
        else
        {
            // no x clipping

            for (int yi = yStart; yi <= yEnd; yi++)
            {
                // compute span endpoints
                int xStart = xl;
                int xEnd = xr;

                // compute starting points for u,v,w interpolants
                int ri = rl;
                int gi = gl;
                int bi = bl;

                // compute u,v interpolants
                int dx = xEnd - xStart;
                int dr, dg, db;
                if (dx > 0)
                {
                    dr = (rr - rl) / dx;
                    dg = (gr - gl) / dx;
                    db = (br - bl) / dx;
                }
                else
                {
                    dr = (rr - rl);
                    dg = (gr - gl);
                    db = (br - bl);
                }

                // draw span
                for (int xi = xStart; xi <= xEnd; xi++)
                {
                    m_fb.wpixel(xi, yi, Color3(ri, gi, bi));

                    // interpolate r, g, b
                    ri += dr;
                    gi += dg;
                    bi += db;
                }

                // interpolate r, g, b, r along right and left edge
                xl += dxdyl;
                rl += drdyl;
                gl += dgdyl;
                bl += dbdyl;

                xr += dxdyr;
                rr += drdyr;
                gr += dgdyr;
                br += dbdyr;

                // test for yi hitting second region, if so change interpolant
                if (yi == yrestart)
                {
                    // test interpolation side change flag

                    if (irestart == INTERP_LHS)
                    {
                        // LHS
                        dyl = y2 - y1;

                        dxdyl = (x2 - x1) / dyl;
                        drdyl = (tr2 - tr1) / dyl;
                        dgdyl = (tg2 - tg1) / dyl;
                        dbdyl = (tb2 - tb1) / dyl;

                        // set starting values
                        xl = x1;
                        rl = tr1;
                        gl = tg1;
                        bl = tb1;

                        // interpolate down on LHS to even up
                        xl += dxdyl;
                        rl += drdyl;
                        gl += dgdyl;
                        bl += dbdyl;
                    }
                    else
                    {
                        // RHS
                        dyr = (y1 - y2);

                        dxdyr = (x1 - x2) / dyr;
                        drdyr = (tr1 - tr2) / dyr;
                        dgdyr = (tg1 - tg2) / dyr;
                        dbdyr = (tb1 - tb2) / dyr;

                        // set starting values
                        xr = x2;
                        rr = tr2;
                        gr = tg2;
                        br = tb2;

                        // interpolate down on RHS to even up
                        xr += dxdyr;
                        rr += drdyr;
                        gr += dgdyr;
                        br += dbdyr;
                    }
                }
            }
        }
    }
}

void Rasterizer::drawGouraudTriangle(const math::Triangle &tr)
{
    drawGouraudTriangle(tr.v(0), tr.v(1), tr.v(2));
}

Rasterizer::Rasterizer(const int width, const int height)
    : m_fb(width, height)
{
}

void Rasterizer::rasterize(const RenderList &rendlist)
{
    const list<math::Triangle> &trias = rendlist.triangles();

    BOOST_REVERSE_FOREACH(const math::Triangle &t, trias)
    {
        if (!t.getMaterial())
        {
            *syslog << "Material has not been setted for this triangle" << logdebug;
            continue;
        }

        switch(t.getMaterial()->shadeMode)
        {
        case Material::SM_WIRE:
            drawTriangle(t);
            break;

        case Material::SM_FLAT:
            drawFillTriangle(t);
            break;

        case Material::SM_GOURAUD:
            drawGouraudTriangle(t);
            break;

        default:
            *syslog << "Unsupported shading mode." << logdebug;
            break;
        }
    }
}

void Rasterizer::beginFrame(/*sptr(RenderDevice) device*/)
{
    m_fb.clear();
}

void Rasterizer::endFrame(/*sptr(RenderDevice) device*/)
{
//    device->flush(m_fb);
}

void Rasterizer::resize(int w, int h)
{
    m_fb.resize(w, h);
}

}
