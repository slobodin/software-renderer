/*
 * texturedtrianglerasterizer.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "texturedtrianglerasterizer.h"

#include "poly.h"
#include "framebuffer.h"
#include "vertex.h"
#include "vec3.h"
#include "color.h"
#include "texture.h"

namespace rend
{

void TexturedTriangleRasterizer::drawTriangle(const math::Triangle &t, FrameBuffer *fb)
{
    math::vertex v0 = t.v(0);
    math::vertex v1 = t.v(1);
    math::vertex v2 = t.v(2);

    static Color3 textel;

    // if triangle isn't on a screen
    if (v2.p.y < fb->yorig() || v0.p.y > fb->height() ||
       (v0.p.x < fb->xorig() && v1.p.x < fb->xorig() && v2.p.x < fb->xorig()) ||
       (v0.p.x > fb->width() && v1.p.x > fb->width() && v2.p.x > fb->width()))
        return;

    if (!t.getMaterial()->texture)
        return;

    Texture *texture = t.getMaterial()->texture.get();    
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

            fb->wpixel(x, y, textel);

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

            fb->wpixel(x, y, textel);

            pu += p_delta_u;
            pv += p_delta_v;
        }
        sdx += dxldy; sdu+=dxldu; sdv+=dxldv;
        edx += dxrdy; edu+=dxrdu; edv+=dxrdv;
    }
}

}
