/*
 * color.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef COLOR4_H
#define COLOR4_H

#include "comm_pch.h"
#include "vec3.h"

namespace rend
{

#ifdef RED
#undef RED
#endif
#ifdef GREEN
#undef GREEN
#endif
#ifdef BLUE
#undef BLUE
#endif
#ifdef ALPHA
#undef ALPHA
#endif

enum ColorComp
{
    RED = 0,
    GREEN,
    BLUE,
    ALPHA
};

inline uint32_t RgbaToInt(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha)
{
    return blue | (green << 8) | (red << 16) | (alpha << 24);
}

inline uint32_t RgbToInt(uint32_t red, uint32_t green, uint32_t blue)
{
    return blue | (green << 8) | (red << 16);
}

inline uint32_t RgbToInt(math::ivec3 color)
{
    return color.z | (color.y << 8) | (color.x << 16);
}

inline uint8_t RedFromInt (int val)
{
    return (val >> 16) & 0xFF;
}

inline uint8_t GreenFromInt (int val)
{
    return (val >> 8) & 0xFF;
}

inline uint8_t BlueFromInt (int val)
{
    return (val & 0xFF);
}

inline uint8_t AlphaFromInt (int val)
{
    return (val >> 24);
}

inline void IntToRgb(uint32_t rgb, uint8_t &red, uint8_t &green, uint8_t &blue)
{
    red = RedFromInt(rgb);
    green = GreenFromInt(rgb);
    blue = BlueFromInt(rgb);
}

class Color4
{
    uint8_t m_color[4];

public:
    Color4();
    Color4(int red, int green,
           int blue, int alpha = 0);
    ~Color4();

    uint32_t color() const { return *((uint32_t *)this); }
    uint8_t r() const { return m_color[0]; }
    uint8_t g() const { return m_color[1]; }
    uint8_t b() const { return m_color[2]; }
    uint8_t a() const { return m_color[3]; }

    uint8_t &operator[](ColorComp ind) { return m_color[ind]; }

    void reset();
};

class Color3
{
    uint32_t m_r;
    uint32_t m_g;
    uint32_t m_b;

public:
    Color3();
    Color3(uint32_t red, uint32_t green, uint32_t blue);
    Color3(uint32_t color);
    ~Color3();

    uint32_t color() const { return RgbToInt(m_r, m_g, m_b); }
    uint8_t red() const { return static_cast<uint8_t>(m_r); }
    uint8_t green() const { return static_cast<uint8_t>(m_g); }
    uint8_t blue() const { return static_cast<uint8_t>(m_b); }

    operator uint32_t() const;
    Color3 &operator*= (double s);
    Color3 &operator*= (const Color3 &other);
    Color3 &operator+= (const Color3 &other);

    friend Color3 operator* (const Color3 &a, const Color3 &b);

    void reset();
};

Color3 operator* (const Color3 &a, const Color3 &b);

}

#endif // COLOR4_H
