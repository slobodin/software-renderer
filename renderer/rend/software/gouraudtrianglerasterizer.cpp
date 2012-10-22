/*
 * gouraudtrianglerasterizer.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "gouraudtrianglerasterizer.h"

#include "poly.h"
#include "framebuffer.h"
#include "vertex.h"
#include "vec3.h"
#include "color.h"
#include <smmintrin.h>

namespace rend
{

// test func
inline bool testClip(const math::vertex &v, FrameBuffer *fb)
{
    int xorig = fb->xorig();
    int yorig = fb->yorig();
    int width = fb->width();
    int height = fb->height();

    return v.p.y < yorig || v.p.y >= height || v.p.x < xorig || v.p.x >= width;
}

union Interpolant
{
    struct { float dr, dg, db, dx; } __attribute__((aligned(16)));
    __m128 v __attribute__((aligned(16)));
};

// TODO: SSE stuff for interpolating
void GouraudTriangleRasterizer::drawTriangle(const math::Triangle &t, FrameBuffer *fb)
{
    math::vertex v0 = t.v(0);
    math::vertex v1 = t.v(1);
    math::vertex v2 = t.v(2);

    // if triangle isn't on a screen
    // without complex clipping......
    /*if (testClip(v0, fb) || testClip(v1, fb) || testClip(v2, fb))
        return;*/

    // CW order
    if (v1.p.y < v0.p.y)
        std::swap(v1, v0);
    if (v2.p.y < v0.p.y)
        std::swap(v0, v2);
    if (v1.p.y < v2.p.y)
        std::swap(v1, v2);

    float dxdy1 = v2.p.x - v0.p.x;
    float dxdr1 = (float)v2.color[RED] - (float)v0.color[RED];
    float dxdg1 = (float)v2.color[GREEN] - (float)v0.color[GREEN];
    float dxdb1 = (float)v2.color[BLUE] - (float)v0.color[BLUE];

    float dxdy2 = v1.p.x - v0.p.x;
    float dxdr2 = (float)v1.color[RED] - (float)v0.color[RED];
    float dxdg2 = (float)v1.color[GREEN] - (float)v0.color[GREEN];
    float dxdb2 = (float)v1.color[BLUE] - (float)v0.color[BLUE];

    float sdx, sdu, sdv, sdw;
    float edx, edu, edv, edw;
    float pu, pv, pw;
    int x, y;

    float dy1 = v2.p.y - v0.p.y;
    float dy2 = v1.p.y - v0.p.y;

    dxdy1 /= dy1;
    dxdr1 /= dy1;
    dxdg1 /= dy1;
    dxdb1 /= dy1;

    dxdy2 /= dy2;
    dxdr2 /= dy2;
    dxdg2 /= dy2;
    dxdb2 /= dy2;

    float dxldy, dxrdy;
    float dxldu, dxrdu;
    float dxldv, dxrdv;
    float dxldw, dxrdw;

    if (dxdy1 < dxdy2)
    {
        dxldy = dxdy1; dxrdy = dxdy2;
        dxldu = dxdr1; dxrdu = dxdr2;
        dxldv = dxdg1; dxrdv = dxdg2;
        dxldw = dxdb1; dxrdw = dxdb2;
    }
    else
    {
        dxldy = dxdy2; dxrdy = dxdy1;
        dxldu = dxdr2; dxrdu = dxdr1;
        dxldv = dxdg2; dxrdv = dxdg1;
        dxldw = dxdb2; dxrdw = dxdb1;
    }

    sdx = v0.p.x; sdu = v0.color[RED]; sdv = v0.color[GREEN]; sdw = v0.color[BLUE];
    edx = v0.p.x; edu = v0.color[RED]; edv = v0.color[GREEN]; edw = v0.color[BLUE];
    pu = v0.color[RED]; pv = v0.color[GREEN]; pw = v0.color[BLUE];

    float p_delta_u;
    float p_delta_v;
    float p_delta_w;

    for (y = (int)v0.p.y; y < (int)v2.p.y; y++)
    {
        p_delta_u = edu - sdu;
        p_delta_v = edv - sdv;
        p_delta_w = edw - sdw;

        p_delta_u /= edx - sdx;
        p_delta_v /= edx - sdx;
        p_delta_w /= edx - sdx;

        pu = sdu; pv = sdv; pw = sdw;

        for (x = (int)sdx; x < (int)edx; x++)
        {
            fb->wpixel(x, y, Color3(pu, pv, pw));

            pu += p_delta_u;
            pv += p_delta_v;
            pw += p_delta_w;
        }

        sdx += dxldy; sdu += dxldu; sdv += dxldv; sdw += dxldw;
        edx += dxrdy; edu += dxrdu; edv += dxrdv; edw += dxrdw;
    }

    // Now for the bottom of the triangle
    if (dxdy1 < dxdy2)
    {
        dxldy = v1.p.x - v2.p.x;
        dxldu = (float)v1.color[RED] - (float)v2.color[RED];
        dxldv = (float)v1.color[GREEN] - (float)v2.color[GREEN];
        dxldw = (float)v1.color[BLUE] - (float)v2.color[BLUE];

        float h = v1.p.y - v2.p.y;
        dxldy /= h;
        dxldu /= h;
        dxldv /= h;
        dxldw /= h;

        sdx = v2.p.x; sdu = v2.color[RED]; sdv = v2.color[GREEN]; sdw = v2.color[BLUE];
    }
    else
    {
        dxrdy = v1.p.x - v2.p.x;
        dxrdu = (float)v1.color[RED] - (float)v2.color[RED];
        dxrdv = (float)v1.color[GREEN] - (float)v2.color[GREEN];
        dxrdw = (float)v1.color[BLUE] - (float)v2.color[BLUE];

        float h = v1.p.y - v2.p.y;
        dxrdy /= h;
        dxrdu /= h;
        dxrdv /= h;
        dxrdw /= h;

        edx = v2.p.x; edu = v2.color[RED]; edv = v2.color[GREEN]; edw = v2.color[BLUE];
    }

    pu = v2.color[RED]; pv = v2.color[GREEN]; pw = v2.color[BLUE];
    for (y = (int)v2.p.y; y< (int)v1.p.y; y++)
    {
        p_delta_u = edu - sdu;
        p_delta_v = edv - sdv;
        p_delta_w = edw - sdw;

        p_delta_u /= edx - sdx;
        p_delta_v /= edx - sdx;
        p_delta_w /= edx - sdx;

        pu = sdu; pv = sdv; pw = sdw;
        for (x = (int)sdx; x < (int)edx; x++)
        {
            fb->wpixel(x, y, Color3(pu, pv, pw));

            pu += p_delta_u;
            pv += p_delta_v;
            pw += p_delta_w;
        }

        sdx += dxldy; sdu += dxldu; sdv += dxldv; sdw += dxldw;
        edx += dxrdy; edu += dxrdu; edv += dxrdv; edw += dxrdw;
    }
}

}
