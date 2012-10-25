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

union Interpolant
{
    struct { float du, dv, dx, dz; } __attribute__((aligned(16)));
    __m128 v __attribute__((aligned(16)));

    Interpolant() : v() { _mm_set_ps1(0.f); }
};

void TexturedTriangleRasterizer::drawTriangle(const math::Triangle &t, FrameBuffer *fb)
{
    math::vertex v0 = t.v(0);
    math::vertex v1 = t.v(1);
    math::vertex v2 = t.v(2);

    static Color3 textel;

    // if triangle isn't on a screen
    /*if (v2.p.y < fb->yorig() || v0.p.y > fb->height() ||
       (v0.p.x < fb->xorig() && v1.p.x < fb->xorig() && v2.p.x < fb->xorig()) ||
       (v0.p.x > fb->width() && v1.p.x > fb->width() && v2.p.x > fb->width()))
        return;*/

    if (!t.getMaterial()->texture)
        return;

    auto material = t.getMaterial();
    Texture *texture = material->texture.get();
    int alpha = material->alpha;
    int texWidth = texture->width();
    int texHeight = texture->height();

    // CW order
    if (v1.p.y < v0.p.y)
        std::swap(v1, v0);
    if (v2.p.y < v0.p.y)
        std::swap(v0, v2);
    if (v1.p.y < v2.p.y)
        std::swap(v1, v2);

    Interpolant leftInt;
    Interpolant rightInt;

    // Interpolating 1/z values.
    leftInt.dx = v2.p.x - v0.p.x;
    leftInt.du = v2.t.x / v2.p.z - v0.t.x / v0.p.z;
    leftInt.dv = v2.t.y / v2.p.z - v0.t.y / v0.p.z;
    leftInt.dz = 1.0f / v2.p.z - 1.0f / v0.p.z;

    rightInt.dx = v1.p.x - v0.p.x;
    rightInt.du = v1.t.x / v1.p.z - v0.t.x / v0.p.z;
    rightInt.dv = v1.t.y / v1.p.z - v0.t.y / v0.p.z;
    rightInt.dz = 1.0f / v1.p.z - 1.0f / v0.p.z;

    float dy1 = v2.p.y - v0.p.y;
    float dy2 = v1.p.y - v0.p.y;

    leftInt.v = _mm_div_ps(leftInt.v, _mm_set_ps1(dy1));
    rightInt.v = _mm_div_ps(rightInt.v, _mm_set_ps1(dy2));

    Interpolant leftIntC;
    Interpolant rightIntC;

    if (leftInt.dx < rightInt.dx)
    {
        leftIntC = leftInt;
        rightIntC = rightInt;
    }
    else
    {
        leftIntC = rightInt;
        rightIntC = leftInt;
    }

    Interpolant start, end;
    start.dx = v0.p.x; start.du = v0.t.x / v0.p.z; start.dv = v0.t.y / v0.p.z; start.dz = 1.0f / v0.p.z;
    end = start;

    Interpolant p, pdelta;

    int x, y;
    for (y = (int)v0.p.y; y < (int)v2.p.y; y++)
    {
        pdelta.v = _mm_sub_ps(end.v, start.v);
        pdelta.dx = 0;

        pdelta.v = _mm_div_ps(pdelta.v, _mm_set_ps1(end.dx - start.dx));

        p = start;

        for (x = (int)start.dx; x < (int)end.dx; x++)
        {
            float u = p.du / 1.0 / p.dz;
            float v = p.dv / 1.0 / p.dz;
            int ww = u * float(texWidth - 1);
            int hh = v * float(texHeight - 1);

            textel = texture->at(ww, hh);

            // modulate by rgb of first vertex (flat shading)
            textel = textel * v0.color;
            textel *= (1.0 / 256.0);        // no /= operator in Color3

            fb->wpixel(x, y, textel, p.dz, alpha);

            p.v = _mm_add_ps(p.v, pdelta.v);
            p.dx = 0;
        }

        start.v = _mm_add_ps(start.v, leftIntC.v);
        end.v = _mm_add_ps(end.v, rightIntC.v);
    }

    // Now for the bottom of the triangle
    if (leftInt.dx < rightInt.dx)
    {
        leftIntC.dx = v1.p.x - v2.p.x;
        leftIntC.du = v1.t.x / v1.p.z - v2.t.x / v2.p.z;
        leftIntC.dv = v1.t.y / v1.p.z - v2.t.y / v2.p.z;
        leftIntC.dz = 1.0f / v1.p.z - 1.0f / v2.p.z;

        leftIntC.v = _mm_div_ps(leftIntC.v, _mm_set_ps1(v1.p.y - v2.p.y));

        start.dx = v2.p.x; start.du = v2.t.x / v2.p.z; start.dv = v2.t.y / v2.p.z; start.dz = 1.0f / v2.p.z;
    }
    else
    {
        rightIntC.dx = v1.p.x - v2.p.x;
        rightIntC.du = v1.t.x / v1.p.z - v2.t.x / v2.p.z;
        rightIntC.dv = v1.t.y / v1.p.z - v2.t.y / v2.p.z;
        rightIntC.dz = 1.0f / v1.p.z - 1.0f / v2.p.z;

        rightIntC.v = _mm_div_ps(rightIntC.v, _mm_set_ps1(v1.p.y - v2.p.y));

        end.dx = v2.p.x; end.du = v2.t.x / v2.p.z; end.dv = v2.t.y / v2.p.z; end.dz = 1.0f / v2.p.z;
    }

    for (y = (int)v2.p.y; y< (int)v1.p.y; y++)
    {
        pdelta.v = _mm_sub_ps(end.v, start.v);
        pdelta.dx = 0;

        pdelta.v = _mm_div_ps(pdelta.v, _mm_set_ps1(end.dx - start.dx));

        p = start;
        for (x = (int)start.dx; x < (int)end.dx; x++)
        {
            float u = p.du / 1.0 / p.dz;
            float v = p.dv / 1.0 / p.dz;
            int ww = u * float(texWidth - 1);
            int hh = v * float(texHeight - 1);

            textel = texture->at(ww, hh);

            // modulate by rgb of first vertex (flat shading)
            textel = textel * v0.color;
            textel *= (1.0 / 256.0);        // no /= operator in Color3

            fb->wpixel(x, y, textel, p.dz, alpha);

            p.v = _mm_add_ps(p.v, pdelta.v);
            p.dx = 0;
        }

        start.v = _mm_add_ps(start.v, leftIntC.v);
        end.v = _mm_add_ps(end.v, rightIntC.v);
    }
}

}
