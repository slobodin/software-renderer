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

/*
 * Scanline algorithm
 */

void FlatTriangleRasterizer::drawTriangle(const math::Triangle &t, FrameBuffer *fb)
{
    math::vertex v0 = t.v(0);
    math::vertex v1 = t.v(1);
    math::vertex v2 = t.v(2);

    // if triangle isn't on a screen
    /*if (v2.p.y < fb->yorig() || v0.p.y > fb->height() ||
       (v0.p.x < fb->xorig() && v1.p.x < fb->xorig() && v2.p.x < fb->xorig()) ||
       (v0.p.x > fb->width() && v1.p.x > fb->width() && v2.p.x > fb->width()))
        return;*/

    // CW order
    if (v1.p.y < v0.p.y)
        std::swap(v1, v0);
    if (v2.p.y < v0.p.y)
        std::swap(v0, v2);
    if (v1.p.y < v2.p.y)
        std::swap(v1, v2);

    float dxleft = v2.p.x - v0.p.x;
    float dzleft = 1.0f / v2.p.z - 1.0f / v0.p.z;

    float dxright = v1.p.x - v0.p.x;
    float dzright = 1.0f / v1.p.z - 1.0f / v0.p.z;

    float dy1 = v2.p.y - v0.p.y;
    float dy2 = v1.p.y - v0.p.y;

    dxleft /= dy1; dzleft /= dy1;
    dxright /= dy2; dzright /= dy2;

    float dxl, dxr, dzl, dzr;

    if (dxleft < dxright)
    {
        dxl = dxleft;
        dzl = dzleft;
        dxr = dxright;
        dzr = dzright;
    }
    else
    {
        dxl = dxright;
        dzl = dzright;
        dxr = dxleft;
        dzr = dzleft;
    }

    float startx, startz, endx, endz;           // start end values
    startx = v0.p.x; startz = 1.0f / v0.p.z;
    endx = startx; endz = startz;

    int x, y;
    float pdeltaz;
    float pz;
    for (y = (int)v0.p.y; y < (int)v2.p.y; y++)
    {
        pdeltaz = endz - startz;
        pdeltaz /= endx - startx;

        pz = startz;

        for (x = (int)startx; x < (int)endx; x++)
        {
            fb->wpixel(x, y, v0.color, pz);

            pz += pdeltaz;
        }

        startx += dxl; startz += dzl;
        endx += dxr; endz += dzr;
    }

    // Now for the bottom of the triangle
    if (dxleft < dxright)
    {
        dxl = v1.p.x - v2.p.x;
        dzl = 1.0f / v1.p.z - 1.0f / v2.p.z;

        dxl /= v1.p.y - v2.p.y;
        dzl /= v1.p.y - v2.p.y;

        startx = v2.p.x; startz = 1.0f / v2.p.z;
    }
    else
    {
        dxr = v1.p.x - v2.p.x;
        dzr = 1.0f / v1.p.z - 1.0f / v2.p.z;

        dxr /= v1.p.y - v2.p.y;
        dzr /= v1.p.y - v2.p.y;

        endx = v2.p.x; endz = 1.0f / v2.p.z;
    }

    for (y = (int)v2.p.y; y < (int)v1.p.y; y++)
    {
        pdeltaz = endz - startz;
        pdeltaz /= endx - startx;

        pz = startz;

        for (x = (int)startx; x < (int)endx; x++)
        {
            fb->wpixel(x, y, v0.color, pz);

            pz += pdeltaz;
        }

        startx += dxl; startz += dzl;
        endx += dxr; endz += dzr;
    }
}

/*
 * Half-space algorithm
 */
//void FlatTriangleRasterizer::drawTriangle(const math::Triangle &t, FrameBuffer *fb)
//{

//}

}
