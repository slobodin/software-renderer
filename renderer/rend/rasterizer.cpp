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

    if (y1 < m_fb.m_yOrigin)
    {
        xs = xs + dxLeft * (-y1 + m_fb.m_yOrigin);
        xe = xe + dxRight * (-y1 + m_fb.m_yOrigin);

        y1 = m_fb.m_yOrigin;
        iy1 = m_fb.m_yOrigin;
    }
    else
    {
        iy1 = y1;

        xs = xs + dxLeft * (iy1 - y1);
        xe = xe + dxRight * (iy1 - y1);
    }
    if (y3 > m_fb.m_height)
    {
        y3 = m_fb.m_height;
        iy3 = y3 - 1;
    }
    else
    {
        iy3 = y3 - 1;
    }

    if (x1 >= m_fb.m_xOrigin && x1 <= m_fb.m_width &&
        x2 >= m_fb.m_xOrigin && x2 <= m_fb.m_width &&
        x3 >= m_fb.m_xOrigin && x3 <= m_fb.m_width)
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

            if (left < m_fb.m_xOrigin)
            {
                left = m_fb.m_xOrigin;

                if (right < m_fb.m_xOrigin)
                    continue;
            }

            if (right > m_fb.m_width)
            {
                right = m_fb.m_width;

                if (left > m_fb.m_width)
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

    if (y1 < m_fb.m_yOrigin)
    {
        xs = xs + dx_left * (-y1 + m_fb.m_yOrigin);
        xe = xe + dx_right * (-y1 + m_fb.m_yOrigin);

        y1 = m_fb.m_yOrigin;

        iy1 = y1;
    }
    else
    {
        iy1 = y1;

        xs = xs + dx_left * (iy1 - y1);
        xe = xe + dx_right * (iy1 - y1);
    }

    if (y3 > m_fb.m_height)
    {
        y3 = m_fb.m_height;

        iy3 = y3 - 1;
    }
    else
    {
        iy3 = y3 - 1;
    }

    if (x1 >= m_fb.m_xOrigin && x1 <= m_fb.m_width &&
        x2 >= m_fb.m_xOrigin && x2 <= m_fb.m_width &&
        x3 >= m_fb.m_xOrigin && x3 <= m_fb.m_width)
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

            if (left < m_fb.m_xOrigin)
            {
                left = m_fb.m_xOrigin;

                if (right < m_fb.m_xOrigin)
                    continue;
            }

            if (right > m_fb.m_width)
            {
                right = m_fb.m_width;

                if (left > m_fb.m_width)
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
    if (p1.y < m_fb.m_yOrigin)
        p1_code |= CLIP_CODE_N;
    else
        if (p1.y > m_fb.m_height)
            p1_code |= CLIP_CODE_S;

    if (p1.x < m_fb.m_xOrigin)
        p1_code |= CLIP_CODE_W;
    else
        if (p1.x > m_fb.m_width)
            p1_code |= CLIP_CODE_E;

    if (p2.y < m_fb.m_yOrigin)
        p2_code |= CLIP_CODE_N;
    else
        if (p2.y > m_fb.m_height)
            p2_code |= CLIP_CODE_S;

    if (p2.x < m_fb.m_xOrigin)
        p2_code |= CLIP_CODE_W;
    else
        if (p2.x > m_fb.m_width)
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
        yc1 = m_fb.m_yOrigin;
        xc1 = p1.x + 0.5 + (m_fb.m_yOrigin - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);

        break;
    case CLIP_CODE_S:
        yc1 = m_fb.m_height;
        xc1 = p1.x + 0.5 + (m_fb.m_height - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);

        break;
    case CLIP_CODE_W:
        xc1 = m_fb.m_xOrigin;
        yc1 = p1.y + 0.5 + (m_fb.m_xOrigin - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);

        break;
    case CLIP_CODE_E:
        xc1 = m_fb.m_width;
        yc1 = p1.y + 0.5 + (m_fb.m_width - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);

        break;
    // these cases are more complex, must compute 2 intersections
    case CLIP_CODE_NE:
        // north hline intersection
        yc1 = m_fb.m_yOrigin;
        xc1 = p1.x + 0.5 + (m_fb.m_yOrigin - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);

        // test if intersection is valid, of so then done, else compute next
        if (xc1 < m_fb.m_xOrigin || xc1 > m_fb.m_width)
        {
            // east vline intersection
            xc1 = m_fb.m_width;
            yc1 = p1.y + 0.5 + (m_fb.m_width - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
        }

        break;
    case CLIP_CODE_SE:
        // south hline intersection
        yc1 = m_fb.m_height;
        xc1 = p1.x + 0.5 + (m_fb.m_height - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);

        // test if intersection is valid, of so then done, else compute next
        if (xc1 < m_fb.m_xOrigin || xc1 > m_fb.m_width)
        {
            // east vline intersection
            xc1 = m_fb.m_width;
            yc1 = p1.y + 0.5 + (m_fb.m_width - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
        } // end if

        break;
    case CLIP_CODE_NW:
        // north hline intersection
        yc1 = m_fb.m_yOrigin;
        xc1 = p1.x + 0.5 + (m_fb.m_yOrigin - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);

        // test if intersection is valid, of so then done, else compute next
        if (xc1 < m_fb.m_xOrigin || xc1 > m_fb.m_width)
        {
            xc1 = m_fb.m_xOrigin;
            yc1 = p1.y + 0.5 + (m_fb.m_xOrigin - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
        } // end if

        break;
    case CLIP_CODE_SW:
        // south hline intersection
        yc1 = m_fb.m_height;
        xc1 = p1.x + 0.5 + (m_fb.m_height - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);

        // test if intersection is valid, of so then done, else compute next
        if (xc1 < m_fb.m_xOrigin || xc1 > m_fb.m_width)
        {
            xc1 = m_fb.m_xOrigin;
            yc1 = p1.y + 0.5 + (m_fb.m_xOrigin - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
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
        yc2 = m_fb.m_yOrigin;
        xc2 = p2.x + (m_fb.m_yOrigin - p2.y) * (p1.x - p2.x) / (p1.y - p2.y);

        break;
    case CLIP_CODE_S:
        yc2 = m_fb.m_height;
        xc2 = p2.x + (m_fb.m_height - p2.y) * (p1.x - p2.x) / (p1.y - p2.y);

        break;
    case CLIP_CODE_W:
        xc2 = m_fb.m_xOrigin;
        yc2 = p2.y + (m_fb.m_xOrigin - p2.x) * (p1.y - p2.y) / (p1.x - p2.x);

        break;
    case CLIP_CODE_E:
        xc2 = m_fb.m_width;
        yc2 = p2.y + (m_fb.m_width - p2.x) * (p1.y - p2.y) / (p1.x - p2.x);

        break;
        // these cases are more complex, must compute 2 intersections
    case CLIP_CODE_NE:
        // north hline intersection
        yc2 = m_fb.m_yOrigin;
        xc2 = p2.x + 0.5 + (m_fb.m_yOrigin - p2.y) * (p1.x - p2.x) / (p1.y - p2.y);

        // test if intersection is valid, of so then done, else compute next
        if (xc2 < m_fb.m_xOrigin || xc2 > m_fb.m_width)
        {
            // east vline intersection
            xc2 = m_fb.m_width;
            yc2 = p2.y + 0.5 + (m_fb.m_width - p2.x) * (p1.y - p2.y) / (p1.x - p2.x);
        }

        break;
    case CLIP_CODE_SE:
        // south hline intersection
        yc2 = m_fb.m_height;
        xc2 = p2.x + 0.5 + (m_fb.m_height - p2.y) * (p1.x - p2.x) / (p1.y - p2.y);

        // test if intersection is valid, of so then done, else compute next
        if (xc2 < m_fb.m_xOrigin || xc2 > m_fb.m_width)
        {
            // east vline intersection
            xc2 = m_fb.m_width;
            yc2 = p2.y + 0.5 + (m_fb.m_width - p2.x) * (p1.y - p2.y) / (p1.x - p2.x);
        }

        break;
    case CLIP_CODE_NW:
        // north hline intersection
        yc2 = m_fb.m_yOrigin;
        xc2 = p2.x + 0.5 + (m_fb.m_yOrigin - p2.y) * (p1.x - p2.x) / (p1.y - p2.y);

        // test if intersection is valid, of so then done, else compute next
        if (xc2 < m_fb.m_xOrigin || xc2 > m_fb.m_width)
        {
            xc2 = m_fb.m_xOrigin;
            yc2 = p2.y + 0.5 + (m_fb.m_xOrigin - p2.x) * (p1.y - p2.y) / (p1.x - p2.x);
        }

        break;
    case CLIP_CODE_SW:
        // south hline intersection
        yc2 = m_fb.m_height;
        xc2 = p2.x + 0.5 + (m_fb.m_height - p2.y) * (p1.x - p2.x) / (p1.y - p2.y);

        // test if intersection is valid, of so then done, else compute next
        if (xc2 < m_fb.m_xOrigin || xc2 > m_fb.m_width)
        {
            xc2 = m_fb.m_xOrigin;
            yc2 = p2.y + 0.5 + (m_fb.m_xOrigin - p2.x) * (p1.y - p2.y) / (p1.x - p2.x);
        }

        break;
    default:
        break;
    }

    // do bounds check
    if ((xc1 < m_fb.m_xOrigin) || (xc1 > m_fb.m_width) ||
        (yc1 < m_fb.m_yOrigin) || (yc1 > m_fb.m_height)||
        (xc2 < m_fb.m_xOrigin) || (xc2 > m_fb.m_width) ||
        (yc2 < m_fb.m_yOrigin) || (yc2 > m_fb.m_height))
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

void Rasterizer::drawLine(const math::vec3 &p1, const math::vec3 &p2, const Color3 &color)
{
    math::vec3 pc1(p1), pc2(p2);

    int cols = m_fb.m_width;

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

void Rasterizer::drawFillTriangle(const math::vec3 &p1,
                                  const math::vec3 &p2,
                                  const math::vec3 &p3,
                                  const Color3 &color)
{
    int x1 = p1.x, x2 = p2.x, x3 = p3.x;
    int y1 = p1.y, y2 = p2.y, y3 = p3.y;

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

    if (y3 < m_fb.m_yOrigin || y1 > m_fb.m_height
            || (x1 < m_fb.m_xOrigin && x2 < m_fb.m_xOrigin && x3 < m_fb.m_xOrigin)
            || (x1 > m_fb.m_width && x2 > m_fb.m_width && x3 > m_fb.m_width))
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

void Rasterizer::drawFillTriangle(const math::Triangle &tr, const Color3 &color)
{
    drawFillTriangle(tr.v(0).p, tr.v(1).p, tr.v(2).p, color);
}

void Rasterizer::drawTriangle(const math::vec3 &p1, const math::vec3 &p2, const math::vec3 &p3, const Color3 &color)
{
    drawLine(p1, p2, color);
    drawLine(p2, p3, color);
    drawLine(p3, p1, color);
}

void Rasterizer::drawTriangle(const math::Triangle &tr, const Color3 &color)
{
    drawTriangle(tr.v(0).p, tr.v(1).p, tr.v(2).p, color);
}

Rasterizer::Rasterizer(const int width, const int height)
    : m_fb(width, height)
{
}

void Rasterizer::rasterize(const RenderList &rendlist)
{
    const list<math::Triangle> &trias = rendlist.triangles();

    reverse_foreach(const math::Triangle &t, trias)
    {
        switch(t.material().shadeMode())
        {
        case Material::SM_WIRE:
            drawTriangle(t, t.material().color());
            break;

        case Material::SM_FLAT:
            drawFillTriangle(t, t.material().color());
            break;

        default:
            *syslog << "Unsupported shading mode." << logwarn;
            break;
        }
    }
}

void Rasterizer::beginFrame()
{
    m_fb.clear();
}

void Rasterizer::endFrame(const string &to)
{
    m_fb.flush_tk(to);
}

void Rasterizer::resize(int w, int h)
{
    m_fb.m_width = w;
    m_fb.m_height = h;

    if (m_fb.m_pixels)
        delete [] m_fb.m_pixels;

    m_fb.m_pixels = new Color3[w * h];
    memset(m_fb.m_pixels, 0xFF, sizeof(Color3) * w * h);
}

}
