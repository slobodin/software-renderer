/*
 * color.cpp
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#include "color.h"

namespace rend
{

Color4::Color4()
    : m_r(0x0),
      m_g(0x0),
      m_b(0x0),
      m_a(0x0)
{
}

Color4::Color4(uint8_t red,
               uint8_t green,
               uint8_t blue,
               uint8_t alpha)
    : m_r(red),
      m_g(green),
      m_b(blue),
      m_a(alpha)
{
}


Color4::~Color4()
{
}

void Color4::reset()
{
    m_r = 0x0;
    m_g = 0x0;
    m_b = 0x0;
    m_a = 0x0;
}

Color3::Color3()
    : m_r(0),
      m_g(0),
      m_b(0)
{
}

Color3::Color3(uint32_t red,
               uint32_t green,
               uint32_t blue)
    : m_r(red),
      m_g(green),
      m_b(blue)
{
}

Color3::Color3(uint32_t color)
{
    m_r = RedFromInt(color);
    m_g = GreenFromInt(color);
    m_b = BlueFromInt(color);
}

Color3::~Color3()
{
}

Color3::operator uint32_t() const
{
    return RgbToInt(m_r, m_g, m_b);
}

void Color3::reset()
{
    m_r = 0;
    m_g = 0;
    m_b = 0;
}

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
