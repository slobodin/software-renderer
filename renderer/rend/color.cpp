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
    : m_r(0x0),
      m_g(0x0),
      m_b(0x0)
{
}

Color3::Color3(uint8_t red,
               uint8_t green,
               uint8_t blue)
    : m_r(red),
      m_g(green),
      m_b(blue)
{
}

Color3::Color3(uint32_t color)
{
    IntToRgb(color, m_r, m_g, m_b);
}

Color3::~Color3()
{
}

Color3 &Color3::operator =(uint32_t color)
{
    IntToRgb(color, m_r, m_g, m_b);

    return *this;
}

Color3::operator uint32_t() const
{
    return RgbToInt(m_r, m_g, m_b);
}

void Color3::reset()
{
    m_r = 0x0;
    m_g = 0x0;
    m_b = 0x0;
}

}
