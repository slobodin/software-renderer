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
#include "mesh.h"
#include "camera.h"
#include "color.h"
#include "material.h"
#include "poly.h"
#include "renderlist.h"
#include "vertex.h"

// LOT OF BOILERPLATE HERE
// don't have enough time to refactor this

namespace rend
{

// helpers
enum TriangleType
{
    TT_FLAT_TOP,
    TT_FLAT_BOTTOM,
    TT_FLAT_GENERAL
};





void Rasterizer::drawGouraudTriangle(math::vertex &v0, math::vertex &v1, math::vertex &v2)
{
    // if triangle isn't on a screen
    if (v2.p.y < m_fb.yorig() || v0.p.y > m_fb.height() ||
       (v0.p.x < m_fb.xorig() && v1.p.x < m_fb.xorig() && v2.p.x < m_fb.xorig()) ||
       (v0.p.x > m_fb.width() && v1.p.x > m_fb.width() && v2.p.x > m_fb.width()))
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
            m_fb.wpixel(x, y, Color3(pu, pv, pw));

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
            m_fb.wpixel(x, y, Color3(pu, pv, pw));

            pu += p_delta_u;
            pv += p_delta_v;
            pw += p_delta_w;
        }
        sdx += dxldy; sdu += dxldu; sdv += dxldv; sdw += dxldw;
        edx += dxrdy; edu += dxrdu; edv += dxrdv; edw += dxrdw;
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

    static Color3 textel;

    // if triangle isn't on a screen
    if (v2.p.y < m_fb.yorig() || v0.p.y > m_fb.height() ||
       (v0.p.x < m_fb.xorig() && v1.p.x < m_fb.xorig() && v2.p.x < m_fb.xorig()) ||
       (v0.p.x > m_fb.width() && v1.p.x > m_fb.width() && v2.p.x > m_fb.width()))
        return;

    Texture *texture = tr.getMaterial()->texture.get();
    int texWidth = texture->width();
    int texHeight = texture->height();

    if (v1.p.y < v0.p.y)
        std::swap(v1, v0);
    if (v2.p.y < v0.p.y)
        std::swap(v0, v2);
    if (v1.p.y < v2.p.y)
        std::swap(v1, v2);

    double dxdy1 = v2.p.x - v0.p.x;
    double dxdu1 = v2.t.x - v0.t.x;
    double dxdv1 = v2.t.y - v0.t.y;

    double dxdy2 = v1.p.x - v0.p.x;
    double dxdu2 = v1.t.x - v0.t.x;
    double dxdv2 = v1.t.y - v0.t.y;

    double sdx,sdu,sdv;
    double edx,edu,edv;
    double pu, pv;
    int x, y;

    double dy1 = v2.p.y - v0.p.y;
    double dy2 = v1.p.y - v0.p.y;

    if (!math::DCMP(v2.p.y, v0.p.y))
    {
        dxdy1 /= dy1;
        dxdu1 /= dy1;
        dxdv1 /= dy1;
    }

    if (!math::DCMP(v1.p.y, v0.p.y))
    {
        dxdy2 /= dy2;
        dxdu2 /= dy2;
        dxdv2 /= dy2;
    }

    double dxldy, dxrdy;
    double dxldu, dxrdu;
    double dxldv, dxrdv;

    if (dxdy1 < dxdy2)
    {
        dxldy = dxdy1; dxrdy = dxdy2;
        dxldu = dxdu1; dxrdu = dxdu2;
        dxldv = dxdv1; dxrdv = dxdv2;
    }
    else
    {
        dxldy = dxdy2; dxrdy = dxdy1;
        dxldu = dxdu2; dxrdu = dxdu1;
        dxldv = dxdv2; dxrdv = dxdv1;
    }

    sdx = v0.p.x; sdu = v0.t.x; sdv = v0.t.y;
    edx = v0.p.x; edu = v0.t.x; edv = v0.t.y;
//    pu = v0.t.x; pv = v0.t.y;

    double p_delta_u;
    double p_delta_v;

    for (y = (int)v0.p.y; y < (int)v2.p.y; y++)
    {
        p_delta_u = edu - sdu;
        p_delta_v = edv - sdv;

        if (!math::DCMP(edx - sdx, 0.))
        {
            p_delta_u /= edx - sdx;
            p_delta_v /= edx - sdx;
        }

        pu = sdu; pv = sdv;

        for (x = (int)sdx; x < (int)edx; x++)
        {
            int ww = pu * (texWidth - 1);
            int hh = pv * (texHeight - 1);

            textel = texture->at(ww, hh);

            // modulate by rgb of first vertex (flat shading)
            textel = textel * v0.color;
            textel *= (1.0 / 256.0);        // no /= operator in Color3

            m_fb.wpixel(x, y, textel);

            pu += p_delta_u;
            pv += p_delta_v;
        }

        sdx += dxldy; sdu += dxldu; sdv += dxldv;
        edx += dxrdy; edu += dxrdu; edv += dxrdv;
    }

    // Now for the bottom of the triangle
    if (dxdy1 < dxdy2)
    {
        dxldy = v1.p.x - v2.p.x;
        dxldu = v1.t.x - v2.t.x;
        dxldv = v1.t.y - v2.t.y;

        if (!math::DCMP(v1.p.y, v2.p.y))
        {
            dxldy /= v1.p.y - v2.p.y;
            dxldu /= v1.p.y - v2.p.y;
            dxldv /= v1.p.y - v2.p.y;
        }

        sdx = v2.p.x; sdu = v2.t.x; sdv = v2.t.y;
    }
    else
    {
        dxrdy = v1.p.x - v2.p.x;
        dxrdu = v1.t.x - v2.t.x;
        dxrdv = v1.t.y - v2.t.y;

        if (!math::DCMP(v1.p.y, v2.p.y))
        {
            dxrdy /= v1.p.y - v2.p.y;
            dxrdu /= v1.p.y - v2.p.y;
            dxrdv /= v1.p.y - v2.p.y;
        }

        edx = v2.p.x; edu = v2.t.x; edv = v2.t.y;
    }

//    pu = v2.t.x; pv = v2.t.y;
    for (y = (int)v2.p.y; y< (int)v1.p.y; y++)
    {
        p_delta_u = edu - sdu;
        p_delta_v = edv - sdv;

        if (!math::DCMP(edx, sdx))
        {
            p_delta_u /= edx - sdx;
            p_delta_v /= edx - sdx;
        }

        pu = sdu; pv = sdv;
        for (x = (int)sdx; x < (int)edx; x++)
        {
            int ww = pu * (texWidth - 1);
            int hh = pv * (texHeight - 1);

            textel = texture->at(ww, hh);

            textel = textel * v0.color;
            textel *= (1.0 / 256.0);        // no /= operator in Color3

            m_fb.wpixel(x, y, textel);

            pu += p_delta_u;
            pv += p_delta_v;
        }
        sdx += dxldy; sdu+=dxldu; sdv+=dxldv;
        edx += dxrdy; edu+=dxrdu; edv+=dxrdv;
    }
}

Rasterizer::Rasterizer(const int width, const int height)
    : m_fb(width, height)
{
}

void Rasterizer::render(const RenderList &rendlist)
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
//            drawTriangle(t);
            break;

        case Material::SM_PLAIN_COLOR:
//            drawFillTriangle(t);
            break;

        case Material::SM_FLAT:
//            drawFillTriangle(t);
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
