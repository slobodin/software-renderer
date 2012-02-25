#include "color.h"

namespace rend
{

Color4::Color4()
    : m_r(0xFF),
      m_g(0xFF),
      m_b(0xFF),
      m_a(0xFF)
{
}

Color4::Color4(const uint8_t red,
               const uint8_t green,
               const uint8_t blue,
               const uint8_t alpha)
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
    m_r = 0xFF;
    m_g = 0xFF;
    m_b = 0xFF;
    m_a = 0xFF;
}

Color3::Color3()
    : m_r(0xFF),
      m_g(0xFF),
      m_b(0xFF)
{
}

Color3::Color3(const uint8_t red,
               const uint8_t green,
               const uint8_t blue)
    : m_r(red),
      m_g(green),
      m_b(blue)
{
}

Color3::Color3(const uint32_t color)
{
    IntToRgb(color, m_r, m_g, m_b);
}

Color3::~Color3()
{
}

void Color3::reset()
{
    m_r = 0xFF;
    m_g = 0xFF;
    m_b = 0xFF;
}

}
