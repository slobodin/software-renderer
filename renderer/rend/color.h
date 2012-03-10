/*
 * color.h
 *
 *  Created on: Mar 10, 2012
 *      Author: flamingo
 */

#ifndef COLOR4_H
#define COLOR4_H

#include "comm_pch.h"

namespace rend
{

inline uint32_t RgbaToInt(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha)
{
    return blue | (green << 8) | (red << 16) | (alpha << 24);
}

inline uint32_t RgbToInt(uint32_t red, uint32_t green, uint32_t blue)
{
    return blue | (green << 8) | (red << 16);
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
    uint8_t m_r;
    uint8_t m_g;
    uint8_t m_b;
    uint8_t m_a;

public:
    Color4();
    Color4(uint8_t red, uint8_t green,
            uint8_t blue, uint8_t alpha);
    ~Color4();

    uint32_t color() const { return RgbaToInt((uint32_t)m_r, (uint32_t)m_g, (uint32_t)m_b, (uint32_t)m_a); }
    uint8_t red() const { return m_r; }
    uint8_t green() const { return m_g; }
    uint8_t blue() const { return m_b; }
    uint8_t alpha() const { return m_a; }

    uint8_t &red() { return m_r; }
    uint8_t &green() { return m_g; }
    uint8_t &blue() { return m_b; }
    uint8_t &alpha() { return m_a; }

    void reset();
};

class Color3
{
    uint8_t m_r;
    uint8_t m_g;
    uint8_t m_b;

public:
    Color3();
    Color3(uint8_t red, uint8_t green, uint8_t blue);
    Color3(uint32_t color);
    ~Color3();

    Color3 &operator= (uint32_t color);

    uint32_t color() const { return RgbToInt((uint32_t)m_r, (uint32_t)m_g, (uint32_t)m_b); }
    uint8_t red() const { return m_r; }
    uint8_t green() const { return m_g; }
    uint8_t blue() const { return m_b; }

    uint8_t &red() { return m_r; }
    uint8_t &green() { return m_g; }
    uint8_t &blue() { return m_b; }

    operator uint32_t() const;

    void reset();
};

}

#endif // COLOR4_H
