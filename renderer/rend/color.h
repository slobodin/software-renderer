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

/** Color convensions:
  * red - from 0 to 255
  * green - from 0 to 255
  * blue - from 0 to 255
  * alpha - 0 transparent, 255 - opaque
  */

//! Color component.
enum ColorComp
{
    ALPHA = 0,
    RED,
    GREEN,
    BLUE
};

//! Converts red, green, blue and alpha components to 32bit integer in A8R8G8B8 format.
inline uint32_t RgbaToInt(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha)
{
    return blue | (green << 8) | (red << 16) | (alpha << 24);
}

//! Converts red, green, blue components to 32bit integer in R8G8B8 format.
inline uint32_t RgbToInt(uint32_t red, uint32_t green, uint32_t blue)
{
    return blue | (green << 8) | (red << 16);
}

//! Returns red component from the 32bit color value.
inline uint8_t RedFromInt (uint32_t val)
{
    return (val >> 16) & 0xFF;
}

//! Returns green component from the 32bit color value.
inline uint8_t GreenFromInt (uint32_t val)
{
    return (val >> 8) & 0xFF;
}

//! Returns blue component from the 32bit color value.
inline uint8_t BlueFromInt (uint32_t val)
{
    return (val & 0xFF);
}

//! Returns alpha component from the 32bit color value.
inline uint8_t AlphaFromInt (uint32_t val)
{
    return (val >> 24);
}

//! Stores red, green and blue components from 32bit int in last three arguments.
inline void IntToRgb(uint32_t rgb, uint8_t &red, uint8_t &green, uint8_t &blue)
{
    red = RedFromInt(rgb);
    green = GreenFromInt(rgb);
    blue = BlueFromInt(rgb);
}

//! Stores red, green, blue and alpha components from 32bit int in last 4 arguments.
inline void IntToRgba(uint32_t rgb, uint8_t &red, uint8_t &green, uint8_t &blue, uint8_t &alpha)
{
    red = RedFromInt(rgb);
    green = GreenFromInt(rgb);
    blue = BlueFromInt(rgb);
    alpha = AlphaFromInt(rgb);
}

//! A8-R8-G8-B8 color.
/*!
  *
  */
class Color4
{
    //! Color array itself.
    uint8_t m_color[4];

public:
    //! Default ctor.
    Color4(int red = 0, int green = 0,
           int blue = 0, int alpha = 255)
    {
        m_color[1] = red;
        m_color[2] = green;
        m_color[3] = blue;
        m_color[0] = alpha;
    }

    //! Dtor.
    ~Color4() { }

    //! Returns raw color in 32bit integer value.
    uint32_t color() const { return *((uint32_t *)this); }
    //! Casts this object to 32bit integer color.
    operator uint32_t() const { return color(); }

    //! Component getter.
    /*! Usage: mycolor[RED] = 128. */
    uint8_t &operator[] (ColorComp ind) { return m_color[ind]; }
    //! Component by-value-getter.
    uint8_t operator[] (ColorComp ind) const { return m_color[ind]; }

    //! Resets to zero.
    void reset() { memset(m_color, 0, sizeof(m_color)); }
};

//! R8-G8-B8 color.
/*!
  *
  */
class Color3
{
    //! Red color.
    uint32_t m_r;
    //! Green color.
    uint32_t m_g;
    //! Blue color.
    uint32_t m_b;

public:
    //! Default ctor.
    Color3()
        : m_r(0), m_g(0), m_b(0)
    { }
    //! Component ctor.
    Color3(uint32_t red, uint32_t green, uint32_t blue)
        : m_r(red), m_g(green), m_b(blue)
    { }

    //! Constructs color from the 32bit integer (R8G8B8).
    Color3(uint32_t color)
    {
        m_r = RedFromInt(color);
        m_g = GreenFromInt(color);
        m_b = BlueFromInt(color);
    }

    //! Dtor.
    ~Color3() { }

    //! Returns raw color in 32bit integer value.
    uint32_t color() const { return RgbToInt(m_r, m_g, m_b); }
    //! Casts this object to 32bit integer color.
    operator uint32_t() const { return color(); }

    //! Component getter.
    /*! Usage: mycolor[RED] = 128. */
    uint32_t &operator[] (ColorComp ind)
    {
        switch (ind)
        {
        case RED:
            return m_r;
        case GREEN:
            return m_g;
        case BLUE:
            return m_b;
        default:
            throw std::out_of_range("Invalid color component");
        }
    }
    //! Component by-value-getter.
    uint32_t operator[] (ColorComp ind) const
    {
        switch (ind)
        {
        case RED:
            return m_r;
        case GREEN:
            return m_g;
        case BLUE:
            return m_b;
        default:
            throw std::out_of_range("Invalid color component");
        }
    }

    //! Color scalar modulation.
    Color3 &operator*= (double s);
    //! Color modulation.
    Color3 &operator*= (const Color3 &other);
    //! Color addition.
    Color3 &operator+= (const Color3 &other);
    //! Color modulation.
    friend Color3 operator* (const Color3 &a, const Color3 &b);

    static Color3 lerp(const Color3 &a, const Color3 &b, double t);

    //! Resets color to zero (black).
    void reset() { m_r = m_g = m_b = 0; }
    //! Checks for zero color.
    bool isBlack() const { return m_r == 0 && m_g == 0 && m_b == 0; }
};

inline Color3 operator* (const Color3 &a, const Color3 &b)
{
    return Color3(a.m_r * b.m_r, a.m_g * b.m_g, a.m_b * b.m_b);
}

inline Color3 Color3::lerp(const Color3 &a, const Color3 &b, double t)
{
    double red = (double)a[RED] + t * ((double)b[RED] - (double)a[RED]);
    double green = (double)a[GREEN] + t * ((double)b[GREEN] - (double)a[GREEN]);
    double blue = (double)a[BLUE] + t * ((double)b[BLUE] - (double)a[BLUE]);

    return Color3(red, green, blue);
}


}

#endif // COLOR4_H
