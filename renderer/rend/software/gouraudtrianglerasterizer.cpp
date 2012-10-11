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

namespace rend
{

void GouraudTriangleRasterizer::drawTriangle(const math::Triangle &t, FrameBuffer *fb)
{
    math::vertex v0 = t.v(0);
    math::vertex v1 = t.v(1);
    math::vertex v2 = t.v(2);

    // if triangle isn't on a screen
    if (v2.p.y < fb->yorig() || v0.p.y > fb->height() ||
       (v0.p.x < fb->xorig() && v1.p.x < fb->xorig() && v2.p.x < fb->xorig()) ||
       (v0.p.x > fb->width() && v1.p.x > fb->width() && v2.p.x > fb->width()))
        return;

    if (v1.p.y < v0.p.y)
        std::swap(v1, v0);
    if (v2.p.y < v0.p.y)
        std::swap(v0, v2);
    if (v1.p.y < v2.p.y)
        std::swap(v1, v2);

    double dxdy1 = v2.p.x - v0.p.x;
    double dxdr1 = (double)v2.color[RED] - (double)v0.color[RED];
    double dxdg1 = (double)v2.color[GREEN] - (double)v0.color[GREEN];
    double dxdb1 = (double)v2.color[BLUE] - (double)v0.color[BLUE];

    double dxdy2 = v1.p.x - v0.p.x;
    double dxdr2 = (double)v1.color[RED] - (double)v0.color[RED];
    double dxdg2 = (double)v1.color[GREEN] - (double)v0.color[GREEN];
    double dxdb2 = (double)v1.color[BLUE] - (double)v0.color[BLUE];

    double sdx, sdu, sdv, sdw;
    double edx, edu, edv, edw;
    double pu, pv, pw;
    int x, y;

    double dy1 = v2.p.y - v0.p.y;
    double dy2 = v1.p.y - v0.p.y;

    if (!math::DCMP(v2.p.y, v0.p.y))
    {
        dxdy1 /= dy1;
        dxdr1 /= dy1;
        dxdg1 /= dy1;
        dxdb1 /= dy1;
    }

    if (!math::DCMP(v1.p.y, v0.p.y))
    {
        dxdy2 /= dy2;
        dxdr2 /= dy2;
        dxdg2 /= dy2;
        dxdb2 /= dy2;
    }

    double dxldy, dxrdy;
    double dxldu, dxrdu;
    double dxldv, dxrdv;
    double dxldw, dxrdw;

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

    double p_delta_u;
    double p_delta_v;
    double p_delta_w;

    for (y = (int)v0.p.y; y < (int)v2.p.y; y++)
    {
        p_delta_u = edu - sdu;
        p_delta_v = edv - sdv;
        p_delta_w = edw - sdw;

        if (!math::DCMP(edx - sdx, 0.))
        {
            p_delta_u /= edx - sdx;
            p_delta_v /= edx - sdx;
            p_delta_w /= edw - sdw;
        }

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
        dxldu = (double)v1.color[RED] - (double)v2.color[RED];
        dxldv = (double)v1.color[GREEN] - (double)v2.color[GREEN];
        dxldw = (double)v1.color[BLUE] - (double)v2.color[BLUE];

        if (!math::DCMP(v1.p.y, v2.p.y))
        {
            double h = v1.p.y - v2.p.y;
            dxldy /= h;
            dxldu /= h;
            dxldv /= h;
            dxldw /= h;
        }

        sdx = v2.p.x; sdu = v2.color[RED]; sdv = v2.color[GREEN]; sdw = v2.color[BLUE];
    }
    else
    {
        dxrdy = v1.p.x - v2.p.x;
        dxrdu = (double)v1.color[RED] - (double)v2.color[RED];
        dxrdv = (double)v1.color[GREEN] - (double)v2.color[GREEN];
        dxrdw = (double)v1.color[BLUE] - (double)v2.color[BLUE];

        if (!math::DCMP(v1.p.y, v2.p.y))
        {
            double h = v1.p.y - v2.p.y;
            dxrdy /= h;
            dxrdu /= h;
            dxrdv /= h;
            dxrdw /= h;
        }

        edx = v2.p.x; edu = v2.color[RED]; edv = v2.color[GREEN]; edw = v2.color[BLUE];
    }

    pu = v2.color[RED]; pv = v2.color[GREEN]; pw = v2.color[BLUE];
    for (y = (int)v2.p.y; y< (int)v1.p.y; y++)
    {
        p_delta_u = edu - sdu;
        p_delta_v = edv - sdv;
        p_delta_w = edw - sdw;

        if (!math::DCMP(edx, sdx))
        {
            p_delta_u /= edx - sdx;
            p_delta_v /= edx - sdx;
            p_delta_w /= edx - sdx;
        }

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
