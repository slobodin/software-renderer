/*
 * trianglerasterizer.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "trianglerasterizer.h"

#include "vertex.h"

namespace rend
{

void TriangleRasterizer::makeCCWTriangle(math::vertex &p1, math::vertex &p2, math::vertex &p3)
{
    // sort vertices (CCW order: p1 (top), p2, p3 (bottom))
    if (p2.p.y < p1.p.y)
        std::swap(p1, p2);

    if (p3.p.y < p1.p.y)
        std::swap(p1, p3);

    if (p3.p.y < p2.p.y)
        std::swap(p2, p3);
}

}

