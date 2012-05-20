/*
 * color.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "color.h"

namespace rend
{

Color3 &Color3::operator*= (double s)
{
    if (s < 0)
        return *this;

    m_r = std::min(m_r * s, 255.0);
    m_g = std::min(m_g * s, 255.0);
    m_b = std::min(m_b * s, 255.0);

    return *this;
}

Color3 &Color3::operator*= (const Color3 &other)
{
    const uint32_t max = 255;
    m_r = std::min(m_r * other.m_r, max);
    m_g = std::min(m_g * other.m_g, max);
    m_b = std::min(m_b * other.m_b, max);

    return *this;
}

Color3 &Color3::operator +=(const Color3 &other)
{
    const uint32_t max = 255;
    m_r = std::min(m_r + other.m_r, max);
    m_g = std::min(m_g + other.m_g, max);
    m_b = std::min(m_b + other.m_b, max);

    return *this;
}

Color3 operator* (const Color3 &a, const Color3 &b)
{
    return Color3(a.m_r * b.m_r, a.m_g * b.m_g, a.m_b * b.m_b);
}

}
